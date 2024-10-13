#include "XZModularComponent.h"
#include "Character/XZCharacter.h"
#include "Manager/XZDataManager.h"
#include "Kismet/KismetMathLibrary.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/World.h"

UXZModularComponent::UXZModularComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
    bWantsInitializeComponent = true;
    Character = nullptr;
}

void UXZModularComponent::InitializeComponent()
{
    Super::InitializeComponent();

    Character = Cast<AXZCharacter>(GetOwner());
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
    USkeletalMeshComponent* SkeletalMeshComponent = GetSkeletalMeshComponent(ModuleType);

    if ( false == IsValid(SkeletalMeshComponent) )
    {
        return;
    }

    // DataManager에서 ItemID의 값을 통해서 Asset 경로를 가지고 온다.
    if ( const UXZDataManager* DataManager = UGameInstance::GetSubsystem<UXZDataManager>(GetWorld()->GetGameInstance()) )
    {
        const FName ModuleIDName = FName(*FString::FromInt(ItemID));

        if ( FItemTable_Module* ModuleAsset = DataManager->TryGetModuleAsset(ModuleIDName) )
        {
            ensure(SkeletalMeshComponent);
            ensure(Character);
            ensure(Character->GetMesh());

            // SkeletalMeshComponent에 SkeletalMesh를 넣어준다.
            if ( USkeletalMesh* SkeletalMesh = LoadObject<USkeletalMesh>(nullptr, *ModuleAsset->ASSETPATH) )
            {
                SkeletalMeshComponent->SetSkeletalMesh(SkeletalMesh);
                if ( SkeletalMeshComponent == Character->GetMesh() ) 
                {
                    return;
                }
                SkeletalMeshComponent->AttachToComponent(Character->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform);
                SkeletalMeshComponent->SetMasterPoseComponent(Character->GetMesh());
            }
            else
            {
                UE_LOG(LogTemp, Error, TEXT("Failed to load SkeletalMesh at path: %s"), *ModuleAsset->ASSETPATH);
            }
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

USkeletalMeshComponent* UXZModularComponent::GetSkeletalMeshComponent(EModularMeshType ModuleType)
{
    TArray<USkeletalMeshComponent*> SkeletalMeshComponents;
    Character->GetComponents(SkeletalMeshComponents);

    // 상체이면 Character의 기본 Mesh를 리턴한다.
    if ( EModularMeshType::Body == ModuleType ) 
    {
        return Character->GetMesh();
    }

    // Component의 Name을 사용해서 해당하는 SkeletalMesh 를 찾는다.
    for ( USkeletalMeshComponent* SkeletalMeshComponent : SkeletalMeshComponents)
    {
        const FString SkeletalMeshName = GetModuleName(ModuleType).ToString() + FString(TEXT("MeshComponent"));

        if ( 0 == SkeletalMeshName.Compare(SkeletalMeshComponent->GetName()) )
        {
            return SkeletalMeshComponent;
        }
    }

    return nullptr;
}
