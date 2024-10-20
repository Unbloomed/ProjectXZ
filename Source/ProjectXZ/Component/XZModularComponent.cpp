#include "XZModularComponent.h"
#include "Character/XZCharacter.h"
#include "Manager/XZDataManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "AssetManager/XZAssetManager.h"
#include "Engine/World.h"

UXZModularComponent::UXZModularComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
}

void UXZModularComponent::InitializeComponent()
{
    Super::InitializeComponent();
}

void UXZModularComponent::BeginPlay()
{
    Super::BeginPlay();

    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EModularMeshType"), true);

    if (false == IsValid(EnumPtr) )
    {
        return;
    }

    for ( int32 i = 0; i < EnumPtr->NumEnums() - 1; ++i )
    {
        const FName ModuleTypeName = *EnumPtr->GetNameStringByIndex(i);
        const EModularMeshType MeshType = static_cast<EModularMeshType>(i);
        if ( UXZDataManager* DataManager = UGameInstance::GetSubsystem<UXZDataManager>(GetWorld()->GetGameInstance()) )
        {
            // DataManager에서 Base Module Item 정보를 가지고 온다.
            if ( FItemTable_ModuleInfo* ModuleInfo = DataManager->TryGetModuleInfo(ModuleTypeName) )
            {
                // 획득 가능하지 않다면
                if (false == ModuleInfo->Obtainable )
                {
                    const int32 BaseModuleIndex = GetBaseModuleItemIndex(ModuleInfo->ID);
                    Attach(MeshType, BaseModuleIndex);
                }
                else 
                {
                    UE_LOG(LogTemp, Log, TEXT("Obtainable Module : [%s]"), *EnumPtr->GetNameStringByIndex(i));
                }
            }
        }
    }
}

void UXZModularComponent::Attach(EModularMeshType ModuleType, int32 ItemID)
{
    // ModuleType으로 해당하는 모듈의 SkeletalMesh를 가지고 온다.
    USkeletalMeshComponent* SkeletalMeshComponent = GetSkeletalMeshComponent(ModuleType);

    if ( false == IsValid(SkeletalMeshComponent) )
    {
        return;
    }

    // ItemID의 값으로 DataManager에서 Asset 경로를 가지고 온다.
    if ( const UXZDataManager* DataManager = UGameInstance::GetSubsystem<UXZDataManager>(GetWorld()->GetGameInstance()) )
    {
        const FName ModuleIDName = FName(*FString::FromInt(ItemID));

        if ( FItemTable_Module* ModuleAsset = DataManager->TryGetModuleAsset(ModuleIDName) )
        {
            ensure(SkeletalMeshComponent);

            UXZAssetManager& AssetManager = UXZAssetManager::GetXZAssetManager();
            FSoftObjectPath AssetPath = ModuleAsset->ASSETPATH;

            AssetManager.GetStreamableManager().RequestAsyncLoad(AssetPath, FStreamableDelegate::CreateLambda([this, SkeletalMeshComponent, AssetPath]()
            {
                    AXZCharacter* Character = Cast<AXZCharacter>(GetOwner());
                    
                    ensure(Character);
                    ensure(Character->GetMesh());

                if (USkeletalMesh* SkeletalMesh = Cast<USkeletalMesh>(AssetPath.TryLoad()))
                {
                    SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);

                    if (SkeletalMeshComponent != Character->GetMesh())
                    {
                        SkeletalMeshComponent->SetMasterPoseComponent(Character->GetMesh()); 
                    }
                }
                else
                {
                    UE_LOG(LogTemp, Error, TEXT("Failed to load SkeletalMesh from path: %s"), *AssetPath.ToString());
                }
            }));
        }
    }
}


void UXZModularComponent::Dettach(EModularMeshType ModuleType)
{
    USkeletalMeshComponent* SkeletalMeshComponent = GetSkeletalMeshComponent(ModuleType);

    if (false == IsValid(SkeletalMeshComponent) )
    {
        return;
    }
    
    SkeletalMeshComponent->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
}


int32 UXZModularComponent::GetBaseModuleItemIndex(const int32 ModuleMainID) const
{
    return ( ( ModuleMainID * 1000 ) + 1 );
}

FName UXZModularComponent::GetModuleName(const EModularMeshType ModuleType)
{
    const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EModularMeshType"), true);
    if ( false ==IsValid(EnumPtr) )
    {
        UE_LOG(LogTemp, Error, TEXT("Invalid EnumPtr for EModularMeshType!"));
        return FName("Invalid");
    }

    const FName ModuleTypeName = FName(*EnumPtr->GetNameStringByIndex(static_cast< int32 >( ModuleType )));

    return ModuleTypeName;
}

USkeletalMeshComponent* UXZModularComponent::GetSkeletalMeshComponent(EModularMeshType ModuleType) const
{
    if ( AXZCharacter* Character = Cast<AXZCharacter>(GetOwner()) ) 
    {
        return Character->GetSkeletalMeshComponent(ModuleType);
    }

    return nullptr;
}
