#include "XZCombat.h"
#include "Engine/SkeletalMeshSocket.h"
#include "GameFramework/Character.h"
#include "ProjectXZ/Weapon/Attachment/XZAttachment.h"
#include "ProjectXZ/Weapon/Projectile/XZProjectile.h"

void UXZCombat::Init(AXZAttachment* InAttachment, ACharacter* InOwner, const TArray<FActionData>& InActionDatas, const FBulletData& InBulletData)
{
	XZAttachment = InAttachment;
	OwnerCharacter = InOwner;
	ActionDatas = InActionDatas;
    BulletData = InBulletData;
}

void UXZCombat::FireAction(const FVector& HitTarget)
{
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
}

void UXZCombat::OnFireBullet(const FVector& HitTargetLocation)
{
	// ¹«±â Nozzle¿¡¼­ ÃÑ¾Ë ¹ß»ç

    if (IsValid(XZAttachment) && IsValid(XZAttachment->GetWeaponMesh()))
    {
        const USkeletalMeshSocket* MuzzleFlashSocket = XZAttachment->GetWeaponMesh()->GetSocketByName(ActionDatas[Idx].MuzzleSocketName);
        if (MuzzleFlashSocket)
        {
            FTransform SocketTransform = MuzzleFlashSocket->GetSocketTransform(XZAttachment->GetWeaponMesh());
            FRotator TargetRotation = (HitTargetLocation - SocketTransform.GetLocation()).Rotation();

            if (IsValid(OwnerCharacter) && IsValid(OwnerCharacter->GetWorld()) && IsValid(ActionDatas[Idx].ProjectileClass))
            {
                UE_LOG(LogTemp, Warning, TEXT("Spawning projectile at location: %s with rotation: %s"), *SocketTransform.GetLocation().ToString(), *TargetRotation.ToString());

                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = XZAttachment->GetOwner();
                SpawnParams.Instigator = Cast<APawn>(XZAttachment->GetOwner());
                SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

                SpawnedProjectile = OwnerCharacter->GetWorld()->SpawnActor<AXZProjectile>(ActionDatas[Idx].ProjectileClass, SocketTransform.GetLocation(), TargetRotation, SpawnParams);
                if (IsValid(SpawnedProjectile))
                {
                    UE_LOG(LogTemp, Warning, TEXT("Projectile spawned successfully"));
                }
            }
        }
    }
}

void UXZCombat::ReloadAction()
{
    if (IsValid(BulletData.ReloadMontage))
    {
        OwnerCharacter->PlayAnimMontage(BulletData.ReloadMontage);

        FTimerHandle ReloadTimerHandle;
        FTimerDelegate ReloadTimerDelegate = FTimerDelegate::CreateUObject(this, &ThisClass::OnRemoveMagazine);
        OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, ReloadTimerDelegate, BulletData.RemoveMagazine_FrameTime, false);

        FTimerHandle ReloadTimerHandle2;
        FTimerDelegate ReloadTimerDelegate2 = FTimerDelegate::CreateUObject(this, &ThisClass::OnAttachNewMagazine);
        OwnerCharacter->GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle2, ReloadTimerDelegate2, BulletData.AttachMagazine_FrameTime, false);
    }
}

void UXZCombat::OnRemoveMagazine()
{

    if (IsValid(XZAttachment) && IsValid(XZAttachment->GetWeaponMesh()))
    {
        const USkeletalMeshSocket* MagazineSocket = XZAttachment->GetWeaponMesh()->GetSocketByName(BulletData.MagazineSocketName);
        if (MagazineSocket)
        {
            FTransform SocketTransform = MagazineSocket->GetSocketTransform(XZAttachment->GetWeaponMesh());
            FRotator TargetRotation = XZAttachment->GetWeaponMesh()->GetRelativeLocation().Rotation();

            if (IsValid(OwnerCharacter) && IsValid(OwnerCharacter->GetWorld()) && IsValid(BulletData.MagazineClass))
            {
                FActorSpawnParameters SpawnParams;
                SpawnParams.Owner = XZAttachment->GetOwner();
                SpawnParams.Instigator = Cast<APawn>(XZAttachment->GetOwner());
                SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

                // ÅºÃ¢ ½ºÆù
                //SpawnedMagazine = OwnerCharacter->GetWorld()->SpawnActor<AActor>(BulletData.MagazineClass, SocketTransform.GetLocation(), TargetRotation, SpawnParams);
                // SpawnedMagazine->AttachToComponent(OwnerCharacter, ); // ¿Þ¼Õ¿¡ ºÎÂø
                //SpawnedMagazine->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
                // TODO: SpawnedMagazine Áß·Â Àû¿ë

                //FTimerHandle DroppedMagazineTimerHandle;
                //FTimerDelegate  DroppedMagazineTimerDelegate = FTimerDelegate::CreateLambda([this]()
                //    {
                //        this->BeginDestroy();
                //    });
                //SpawnedMagazine->GetWorld()->GetTimerManager().SetTimer(DroppedMagazineTimerHandle, DroppedMagazineTimerDelegate, 3.0f, false);
            }
        }
    }
}

void UXZCombat::OnAttachNewMagazine()
{
}
