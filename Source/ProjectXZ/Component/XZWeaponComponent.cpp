#include "XZWeaponComponent.h"

#include "XZStateComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "ProjectXZ/Character/XZCharacter.h"
#include "ProjectXZ/Character/XZPlayerController.h"
#include "ProjectXZ/GameplayTag/XZGameplayTags.h"
#include "ProjectXZ/HUD/XZHUD.h"
#include "ProjectXZ/Weapon/XZDA_Weapon.h"
#include "ProjectXZ/Weapon/XZEquipment.h"
#include "ProjectXZ/Weapon/XZWeaponData.h"
#include "ProjectXZ/Weapon/Combat/XZCombat.h"
#include "Weapon/Attachment/XZAttachment.h"

UXZWeaponComponent::UXZWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
	//SetIsReplicated(true);
}

void UXZWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UXZWeaponComponent, EquippedWeaponTag, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UXZWeaponComponent, bIsAiming, COND_None, REPNOTIFY_Always);
	//DOREPLIFETIME(UXZWeaponComponent, bIsAiming);
}

void UXZWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetXZCharacter() && GetXZCharacter()->IsLocallyControlled())
	{
		FHitResult HitResult;
		TraceUnderCrosshairs(HitResult); // Crosshair���� LineTrace�� ��� HitResult ���� ������Ʈ�Ѵ�.
		HitTarget = HitResult.ImpactPoint;

		SetHUDCrosshairs(DeltaTime);
		InterpFOV(DeltaTime);
	}
}

TObjectPtr<AXZCharacter> UXZWeaponComponent::GetXZCharacter()
{
	if (IsValid(OwnerCharacter)) return OwnerCharacter;

	OwnerCharacter = Cast<AXZCharacter>(GetOwner());
	return OwnerCharacter;
}

TObjectPtr<AXZPlayerController> UXZWeaponComponent::GetXZPlayerController()
{
	if (IsValid(XZPlayerController)) return XZPlayerController;

	XZPlayerController = Cast<AXZPlayerController>(GetXZCharacter()->GetController());
	return XZPlayerController;
}

TObjectPtr<AXZHUD> UXZWeaponComponent::GetXZHUD()
{
	if (XZHUD) return XZHUD;

	XZHUD = Cast<AXZHUD>(GetXZPlayerController()->GetHUD());
	return XZHUD;
}

void UXZWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	// ���� ���
	for (const TTuple<FGameplayTag, UXZDA_Weapon*>& Weapon : WeaponList)
	{
		UXZWeaponData* Temp = NewObject<UXZWeaponData>(this);
		Datas.Add(Weapon.Key, Temp);
	}

	// ���� ���� ����
	for (const FGameplayTag& Tag : Init_WeaponTags)
	{
		WeaponList[Tag]->CreateInstance(GetXZCharacter(), &Datas[Tag]);
	}
}

void UXZWeaponComponent::AddNewWeapon(const FGameplayTag& InTag)
{
	Server_AddNewWeapon(InTag);
}

void UXZWeaponComponent::Server_AddNewWeapon_Implementation(const FGameplayTag& InTag)
{
	Multicast_AddNewWeapon(InTag);
}

void UXZWeaponComponent::Multicast_AddNewWeapon_Implementation(const FGameplayTag& InTag)
{
	WeaponList[InTag]->CreateInstance(GetXZCharacter(), &Datas[InTag]);
}

void UXZWeaponComponent::TraceUnderCrosshairs(FHitResult& TraceHitResult)
{
	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}

	FVector2D CrosshairLocation(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f); // ȭ�� �߾�
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CrosshairLocation,
		CrosshairWorldPosition,
		CrosshairWorldDirection
	); // DeprojectScreenToWorld �����ϸ� true, �����ϸ� false

	if (bScreenToWorld)
	{
		FVector Start = CrosshairWorldPosition;

		if (GetXZCharacter())
		{
			float DistanceToCharacter = (GetXZCharacter()->GetActorLocation() - Start).Size();
			Start += CrosshairWorldDirection * (DistanceToCharacter + 100.0f);
			//DrawDebugSphere(GetWorld(), Start, 4.0f, 12, FColor::Blue, false); // ������
		}

		FVector End = Start + CrosshairWorldDirection * 80000.0f; // TRACE_LENGTH 80000.0f

		GetWorld()->LineTraceSingleByChannel(TraceHitResult, 	Start, End, ECollisionChannel::ECC_Visibility);

		if (TraceHitResult.bBlockingHit == false) // �ϴ� ���� �浹�Ұ� ���°��� ��� ���
		{
			TraceHitResult.ImpactPoint = End; // �浹�ϴ°� ���ٸ� End ���� ImpactPoint������ ����.
		}
		
	}
}

void UXZWeaponComponent::EquipWeapon(const FGameplayTag& InTag)
{
	Server_EquipWeapon(InTag);
}


void UXZWeaponComponent::OnRep_EquippedChanged()
{

}

void UXZWeaponComponent::Server_EquipWeapon_Implementation(const FGameplayTag& InTag)
{
	EquippedWeaponTag = InTag;
	Multicast_EquipWeapon(InTag);
}

void UXZWeaponComponent::Multicast_EquipWeapon_Implementation(const FGameplayTag& InTag)
{
	// ���Կ� ��ϵ� ������ GameplayTag�� InTag�� ������
	
	if (UXZWeaponData** FoundData = Datas.Find(InTag))
	{
		if (*FoundData)
		{
			if (Datas[InTag]->GetEquipment()->Equip()) // �������� O
			{

			}
			else // �������� X (= Unequip ������ ���)
			{
				Datas[InTag]->GetEquipment()->Unequip();
				EquippedWeaponTag = FXZTags::GetXZTags().Fist;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FoundData(=XZWeaponData) is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Weapon is not found. Check UXZWeaponComponent::EquipWeapon"));
	}
}


void UXZWeaponComponent::Fire()
{
	if (false == EquippedWeaponTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Weapon"))))) return; // ���� ���� ���� �ƴ϶�� return

	if (GetXZCharacter() && GetXZCharacter()->IsLocallyControlled())
	{
		const USkeletalMeshSocket* MuzzleFlashSocket = Datas[EquippedWeaponTag]->GetAttachment()->GetWeaponMesh()->GetSocketByName(
			Datas[EquippedWeaponTag]->GetCombat()->GetActionData()[0].MuzzleSocketName);
		FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(Datas[EquippedWeaponTag]->GetAttachment()->GetWeaponMesh());
			
		Server_Fire(HitTarget, SocketTransform);
	}
}

void UXZWeaponComponent::Server_Fire_Implementation(const FVector_NetQuantize& HitLocation, const FTransform& SocketTransform)
{
	Multicast_Fire(HitLocation, SocketTransform);
}

void UXZWeaponComponent::Multicast_Fire_Implementation(const FVector_NetQuantize& HitLocation, const FTransform& SocketTransform)
{
	if (UXZWeaponData** FoundData = Datas.Find(EquippedWeaponTag))
	{
		if (*FoundData)
		{
			if (Datas[EquippedWeaponTag]->GetCombat()->GetBulletData().Ammo <= 0) // �Ѿ��� ���ٸ�
			{
				Reload(EquippedWeaponTag); // ������
				return;
			}
			
			UE_LOG(LogTemp, Warning, TEXT("Ammo = %d"), Datas[EquippedWeaponTag]->GetCombat()->GetBulletData().Ammo);
			Datas[EquippedWeaponTag]->GetCombat()->FireAction(HitLocation, SocketTransform);
			Datas[EquippedWeaponTag]->GetCombat()->ConsumeAmmo();

			if (Datas[EquippedWeaponTag]->GetCombat()->GetBulletData().Ammo <= 0) // �Ѿ��� ���ٸ�
			{
				Reload(EquippedWeaponTag); // ������
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FoundData(=XZWeaponData) is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameplayTag is not found in Datas"));
	}
}

void UXZWeaponComponent::Reload(const FGameplayTag& InTag)
{
	if (Datas[InTag]->GetCombat()->GetBulletData().TotalAmmo <= 0) 
	{
		UE_LOG(LogTemp, Warning, TEXT("Run out of Bullets"));
		return; // �Ѿ� ���� ��� return
	}

	const USkeletalMeshSocket* MagazineSocket = Datas[EquippedWeaponTag]->GetAttachment()->GetWeaponMesh()->GetSocketByName(
		Datas[EquippedWeaponTag]->GetCombat()->GetBulletData().CasingSocketName);
	FTransform SocketTransform = MagazineSocket->GetSocketTransform(Datas[EquippedWeaponTag]->GetAttachment()->GetWeaponMesh());


	Server_Reload(InTag, SocketTransform);


	if (UXZWeaponData** FoundData = Datas.Find(InTag))
	{
		if (*FoundData)
		{
			// �Ѿ� ä���
			if (Datas[InTag]->GetCombat()->GetBulletData().TotalAmmo >= Datas[InTag]->GetCombat()->GetBulletData().MagCapacity)
			{
				Datas[InTag]->GetCombat()->GetBulletData().Ammo = Datas[InTag]->GetCombat()->GetBulletData().MagCapacity;
				Datas[InTag]->GetCombat()->GetBulletData().TotalAmmo -= Datas[InTag]->GetCombat()->GetBulletData().MagCapacity;
			}
			else
			{
				Datas[InTag]->GetCombat()->GetBulletData().Ammo = Datas[InTag]->GetCombat()->GetBulletData().TotalAmmo;
				Datas[InTag]->GetCombat()->GetBulletData().TotalAmmo = 0;
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("FoundData(=XZWeaponData) is nullptr"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("GameplayTag is not found in Datas"));
	}
}

void UXZWeaponComponent::Server_Reload_Implementation(const FGameplayTag& InTag, const FTransform& SocketTransform)
{
	Multicast_Reload(InTag, SocketTransform);
}

void UXZWeaponComponent::Multicast_Reload_Implementation(const FGameplayTag& InTag, const FTransform& SocketTransform)
{
	Datas[InTag]->GetCombat()->ReloadAction(SocketTransform);
}

void UXZWeaponComponent::Aiming(bool bAiming)
{
	if (false == IsValid(GetXZCharacter())) return;

	bIsAiming = bAiming;
}

void UXZWeaponComponent::OnRep_Aiming()
{
	if (bIsAiming)
	{
		GetXZCharacter()->GetStateComponent()->SetState(FXZTags::GetXZTags().StateTag_Alive_Equip_Aim);
		GetXZCharacter()->GetCharacterMovement()->MaxWalkSpeed = AimWalkSpeed;
	}
	else
	{
		GetXZCharacter()->GetStateComponent()->SetState(FXZTags::GetXZTags().StateTag_Alive_Equip_Idle);
		GetXZCharacter()->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	}
}

void UXZWeaponComponent::InterpFOV(float InDeltaTime)
{
	if (false == EquippedWeaponTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Weapon"))))) return; // ���� ���� ���� �ƴ϶�� return

	if (bIsAiming)
	{
		CurrentFOV = FMath::FInterpTo(CurrentFOV, ZoomedFOV, InDeltaTime, 20.0f);
	}
	else
	{
		CurrentFOV = FMath::FInterpTo(CurrentFOV, DefaultFOV, InDeltaTime, 20.0f);
	}

	GetXZCharacter()->GetFollowCamera()->SetFieldOfView(CurrentFOV);
}

void UXZWeaponComponent::SetHUDCrosshairs(float InDeltaTime)
{
	if (false == IsValid(GetXZCharacter()) || false == IsValid(GetXZPlayerController())) return;
	if (false == IsValid(GetXZHUD())) return;
	
	if (EquippedWeaponTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Weapon")))))
	{
		// TODO: ���� �� Crosshair �����ϱ�
		GetXZHUD()->CrosshairTexture2D = CrosshairTexture2D;
		GetXZHUD()->DrawHUD();
	}
	else
	{
		GetXZHUD()->CrosshairTexture2D = nullptr;
	}
}
