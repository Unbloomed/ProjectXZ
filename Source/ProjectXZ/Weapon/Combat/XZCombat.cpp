#include "XZCombat.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectXZ/Weapon/Attachment/XZAttachment.h"
#include "ProjectXZ/Weapon/Projectile/XZProjectile.h"
#include "Weapon/Casing/XZCasing.h"
#include "Weapon/Magazine/XZMagazine.h"

void UXZCombat::Init(AXZAttachment* InAttachment, ACharacter* InOwner, const TArray<FActionData>& InActionDatas, const FBulletData& InBulletData)
{
	XZAttachment = InAttachment;
	OwnerCharacter = InOwner;
	ActionDatas = InActionDatas;
    BulletData = InBulletData;
}

void UXZCombat::FireAction(const FVector_NetQuantize& HitTarget)
{
    if (false == IsValid(OwnerCharacter) && false == IsValid(OwnerCharacter->GetWorld())) return;

    // 공격 몽타주 재생 & 총알 발사
	if (IsValid(ActionDatas[Idx].ActionMontage))
	{
		OwnerCharacter->PlayAnimMontage(ActionDatas[Idx].ActionMontage);

        FTimerHandle FireTimerHandle;
        //FTimerDelegate FireTimerDelegate = FTimerDelegate::CreateUObject(this, &ThisClass::OnFireBullet, HitTarget);
        FTimerDelegate FireTimerDelegate = FTimerDelegate::CreateLambda([this, HitTarget]()
            {
                this->OnFireBullet(HitTarget);
            });
        OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, FireTimerDelegate, ActionDatas[Idx].Action_FrameTime, false);
    }

    // 총 애니메이션
    if (IsValid(ActionDatas[Idx].GunFireAnimation))
    {
        XZAttachment->GetWeaponMesh()->PlayAnimation(ActionDatas[Idx].GunFireAnimation, false);
    }
}

void UXZCombat::OnFireBullet(const FVector_NetQuantize& HitTargetLocation)
{
    if (IsValid(XZAttachment) && IsValid(XZAttachment->GetWeaponMesh()))
    {
        //*******************************************************************************
        //** 무기 Nozzle에서 총알 발사
        if (OwnerCharacter->HasAuthority()) // 총알은 서버에서만 발사
        {
	        const USkeletalMeshSocket* MuzzleFlashSocket = XZAttachment->GetWeaponMesh()->GetSocketByName(ActionDatas[Idx].MuzzleSocketName);
	        if (IsValid(MuzzleFlashSocket))
	        {
	            FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(XZAttachment->GetWeaponMesh());
	            FRotator TargetRotation = (HitTargetLocation - SocketTransform.GetLocation()).Rotation();

	            if (IsValid(ActionDatas[Idx].ProjectileClass))
	            {
	                UE_LOG(LogTemp, Warning, TEXT("Spawning projectile at location: %s with rotation: %s"), *SocketTransform.GetLocation().ToString(), *TargetRotation.ToString());

	                FActorSpawnParameters SpawnParams;
	                SpawnParams.Owner = XZAttachment->GetOwner();
	                SpawnParams.Instigator = Cast<APawn>(XZAttachment->GetOwner());
	                SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	                SpawnedProjectile = OwnerCharacter->GetWorld()->SpawnActor<AXZProjectile>(ActionDatas[Idx].ProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParams);
	            }
	        }
        }
        //*******************************************************************************

        //*******************************************************************************
        if (false == OwnerCharacter->HasAuthority())
        {
	        // 발사 사운드
	        if (IsValid(ActionDatas[Idx].FireSound))
	        {
	            UGameplayStatics::PlaySoundAtLocation(XZAttachment->GetWeaponMesh(), ActionDatas[Idx].FireSound, XZAttachment->GetWeaponMesh()->GetComponentLocation());
	        }

	        // 탄피 배출
	        if (IsValid(BulletData.CasingClass))
	        {
	            const USkeletalMeshSocket* AmmoEjectSocket = XZAttachment->GetWeaponMesh()->GetSocketByName(BulletData.CasingSocketName);
	            if (IsValid(AmmoEjectSocket))
	            {
	                FTransform SocketTransform = AmmoEjectSocket->GetSocketTransform(XZAttachment->GetWeaponMesh());

	                OwnerCharacter->GetWorld()->SpawnActor<AXZCasing>(BulletData.CasingClass, SocketTransform.GetLocation(), SocketTransform.GetRotation().Rotator());
	            }
	        }
        }
        //*******************************************************************************
    }
}

void UXZCombat::ReloadAction()
{
    if (IsValid(BulletData.ReloadMontage))
    {
        OwnerCharacter->PlayAnimMontage(BulletData.ReloadMontage);

        FTimerHandle ReloadTimerHandle;
        FTimerDelegate ReloadTimerDelegate = FTimerDelegate::CreateUObject(this, &ThisClass::OnEjectMagazine);
        OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, ReloadTimerDelegate, BulletData.EjectMagazine_FrameTime, false);

        FTimerHandle ReloadTimerHandle2;
        FTimerDelegate ReloadTimerDelegate2 = FTimerDelegate::CreateUObject(this, &ThisClass::OnAttachNewMagazine);
        OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle2, ReloadTimerDelegate2, BulletData.AttachMagazine_FrameTime, false);
    }
}

void UXZCombat::OnEjectMagazine()
{
    if (IsValid(XZAttachment) && IsValid(XZAttachment->GetWeaponMesh()))
    {
        if (BulletData.MagazineSocketName.IsValid())
        {
            XZAttachment->GetWeaponMesh()->HideBoneByName(BulletData.MagazineSocketName, EPhysBodyOp::PBO_None);
            

        	FTransform SocketTransform = XZAttachment->GetWeaponMesh()->GetSocketTransform(BulletData.MagazineSocketName);

            if (IsValid(OwnerCharacter) && IsValid(OwnerCharacter->GetWorld()) && IsValid(BulletData.MagazineClass))
            {
                // 탄창 스폰
                EjectedMagazine = OwnerCharacter->GetWorld()->SpawnActorDeferred<AXZMagazine>(BulletData.MagazineClass, SocketTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AlwaysSpawn);
                EjectedMagazine->FinishSpawning(SocketTransform);
                //EjectedMagazine->AttachToActor(OwnerCharacter, FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("hand_l")));
                EjectedMagazine->SetLifeSpan(5.0f);
                EjectedMagazine->SetEject();

                FTimerHandle EjectTimerHandle;
                OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(EjectTimerHandle, FTimerDelegate::CreateLambda([this](){
                    this->OnThrowMagazineToGround();
                }), BulletData.ThrowMagazine_FrameTime, false);
            }
        }
    }
}

void UXZCombat::OnThrowMagazineToGround()
{
    //EjectedMagazine->DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
}

void UXZCombat::OnAttachNewMagazine()
{
    FActorSpawnParameters params;
    params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

    NewMagazine = OwnerCharacter->GetWorld()->SpawnActor<AXZMagazine>(BulletData.MagazineClass, params);
    NewMagazine->AttachToActor(OwnerCharacter, FAttachmentTransformRules::KeepRelativeTransform, FName(TEXT("hand_l")));
}
