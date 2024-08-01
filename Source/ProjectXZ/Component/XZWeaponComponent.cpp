#include "XZWeaponComponent.h"
#include "Camera/CameraComponent.h"
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

UXZWeaponComponent::UXZWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicatedByDefault(true);
}

void UXZWeaponComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UXZWeaponComponent, EquippedWeaponTag, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME(UXZWeaponComponent, bIsAiming);
}

void UXZWeaponComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetXZCharacter() && GetXZCharacter()->IsLocallyControlled())
	{
		FHitResult HitResult;
		TraceUnderCrosshairs(HitResult); // Crosshair에서 LineTrace를 쏘고 HitResult 값을 업데이트한다.
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

	// 무기 목록
	for (const TTuple<FGameplayTag, UXZDA_Weapon*>& Weapon : WeaponList)
	{
		UXZWeaponData* Temp = NewObject<UXZWeaponData>(this);
		Datas.Add(Weapon.Key, Temp);
	}

	// 시작 무기 생성
	for (const FGameplayTag& Tag : Init_WeaponTags)
	{
		WeaponList[Tag]->CreateInstance(GetXZCharacter(), &Datas[Tag]);
	}
}

void UXZWeaponComponent::TraceUnderCrosshairs(FHitResult& TraceHitResult)
{
	FVector2D ViewportSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewportSize);
	}

	FVector2D CrosshairLocation(ViewportSize.X / 2.0f, ViewportSize.Y / 2.0f); // 화면 중앙
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CrosshairLocation,
		CrosshairWorldPosition,
		CrosshairWorldDirection
	); // DeprojectScreenToWorld 성공하면 true, 실패하면 false

	if (bScreenToWorld)
	{
		FVector Start = CrosshairWorldPosition;

		if (GetXZCharacter())
		{
			float DistanceToCharacter = (GetXZCharacter()->GetActorLocation() - Start).Size();
			Start += CrosshairWorldDirection * (DistanceToCharacter + 100.0f);
			//DrawDebugSphere(GetWorld(), Start, 4.0f, 12, FColor::Blue, false); // 디버깅용
		}

		FVector End = Start + CrosshairWorldDirection * 80000.0f; // TRACE_LENGTH 80000.0f

		GetWorld()->LineTraceSingleByChannel(TraceHitResult, 	Start, End, ECollisionChannel::ECC_Visibility);

		if (TraceHitResult.bBlockingHit == false) // 하늘 같이 충돌할게 없는곳에 쏘는 경우
		{
			TraceHitResult.ImpactPoint = End; // 충돌하는게 없다면 End 값을 ImpactPoint값으로 설정.
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
	// 슬롯에 등록된 무기의 GameplayTag를 InTag로 가져옴
	
	if (UXZWeaponData** FoundData = Datas.Find(InTag))
	{
		if (*FoundData)
		{
			if (Datas[InTag]->GetEquipment()->Equip()) // 무기장착 O
			{

			}
			else // 무기장착 X (= Unequip 수행한 경우)
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
	if (GetXZCharacter() && GetXZCharacter()->IsLocallyControlled())
	{
		Server_Fire(HitTarget);
	}
}

void UXZWeaponComponent::Server_Fire_Implementation(const FVector_NetQuantize& HitLocation)
{
	Multicast_Fire(EquippedWeaponTag, HitLocation);
}

void UXZWeaponComponent::Multicast_Fire_Implementation(const FGameplayTag& InTag, const FVector_NetQuantize& HitLocation)
{
	if (UXZWeaponData** FoundData = Datas.Find(InTag))
	{
		if (*FoundData)
		{
			if (Datas[InTag]->GetCombat()->GetBulletData().Ammo <= 0) // 총알이 없다면
			{
				Reload(InTag); // 재장전
				return;
			}
			
			UE_LOG(LogTemp, Warning, TEXT("Ammo = %d"), Datas[InTag]->GetCombat()->GetBulletData().Ammo);
			Datas[InTag]->GetCombat()->FireAction(HitLocation);
			Datas[InTag]->GetCombat()->ConsumeAmmo();

			if (Datas[InTag]->GetCombat()->GetBulletData().Ammo <= 0) // 총알이 없다면
			{
				Reload(InTag); // 재장전
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
	if (Datas[InTag]->GetCombat()->GetBulletData().TotalAmmo <= 0) return; // 총알 없는 경우 return

	if (UXZWeaponData** FoundData = Datas.Find(InTag))
	{
		if (*FoundData)
		{
			Datas[InTag]->GetCombat()->ReloadAction();

			// 총알 채우기
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

void UXZWeaponComponent::StartAiming()
{
	if (false == IsValid(GetXZCharacter())) return;

	GetXZCharacter()->GetCharacterMovement()->MaxWalkSpeed = AimWalkSpeed;
	bIsAiming = true;
}

void UXZWeaponComponent::EndAiming()
{
	if (false == IsValid(GetXZCharacter())) return;

	GetXZCharacter()->GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	bIsAiming = false;
}

void UXZWeaponComponent::InterpFOV(float InDeltaTime)
{
	if (false == EquippedWeaponTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName(TEXT("Weapon"))))) return; // 무기 장착 중이 아니라면 return

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
		// TODO: 무기 별 Crosshair 설정하기
		GetXZHUD()->CrosshairTexture2D = CrosshairTexture2D;
		GetXZHUD()->DrawHUD();
	}
	else
	{
		GetXZHUD()->CrosshairTexture2D = nullptr;
	}
}
