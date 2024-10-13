#include "Widget/XZModuleSelectSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Manager/XZDataManager.h"
#include "Kismet/KismetMaterialLibrary.h"

// 인터페이스 사용하기
#include "Character/XZCharacter.h"
#include "Component/XZModularComponent.h"

UXZModuleSelectSlot::UXZModuleSelectSlot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	CurrentIndex = 0;

	SlotMaterialInstanceDynamic = CreateDefaultSubobject<UMaterialInstanceDynamic>(TEXT("SlotMaterialInstanceDynamic"));
}

void UXZModuleSelectSlot::NativeConstruct()
{
	Super::NativeConstruct();

	if ( PrevButton )
	{
		PrevButton->OnClicked.AddDynamic(this, &UXZModuleSelectSlot::OnPrevButtonClicked);
	}

	if ( NextButton )
	{
		NextButton->OnClicked.AddDynamic(this, &UXZModuleSelectSlot::OnNextButtonClicked);
	}
}

void UXZModuleSelectSlot::OnPrevButtonClicked()
{
	if ( CurrentIndex  < 1)
	{
		return;
	}
	SetCurrentSelectItemID(--CurrentIndex);
	OnModuleChanged.Broadcast(ModuleType, CurrentIndex + IndexInfo.ItemBaseID );
}

void UXZModuleSelectSlot::OnNextButtonClicked()
{
	if ( CurrentIndex > IndexInfo.ItemLastID - IndexInfo.ItemBaseID - 1)
	{
		return;
	}
	SetCurrentSelectItemID(++CurrentIndex);
	OnModuleChanged.Broadcast(ModuleType, CurrentIndex + IndexInfo.ItemBaseID);
}

void UXZModuleSelectSlot::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	IUserObjectListEntry::NativeOnListItemObjectSet(ListItemObject);
	
	// 데이터 설정하기
	UXZModuleSelectSlotItem* SlotItem = Cast<UXZModuleSelectSlotItem>(ListItemObject);

	IndexInfo = SlotItem->GetIndexInfo();
	ModuleType = SlotItem->GetSlotInfo().ModuleType;
	SlotMaterialInstance = SlotItem->GetSlotInfo().SlotMaterialInstance;

	////////////////////////////////////////////// Debugging //////////////////////////////////////////////
	/*
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EModularMeshType"), true);
	if ( false == IsValid(EnumPtr) )
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("[%s] :%d ~ %d"),*EnumPtr->GetNameStringByIndex(static_cast< int32 >( SlotItem->GetSlotInfo().ModuleType )), IndexInfo.ItemBaseID, IndexInfo.ItemLastID);
	*/
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	SetCurrentSelectItemID(0);

	if ( AXZCharacter* Character = Cast< AXZCharacter>(GetOwningPlayerPawn()) ) 
	{
		if ( UXZModularComponent* ModularComponent = Character->GetModularComponent() ) 
		{
			OnModuleChanged.AddUObject(ModularComponent, &UXZModularComponent::Attach);
		}
	}
}

void UXZModuleSelectSlot::SetModuleType(const EModularMeshType NewModuleType)
{
	ModuleType = NewModuleType;
}

void UXZModuleSelectSlot::SetModuleImage()
{
	if ( false == IsValid(PreviewImage) )
	{
		return;
	}

	if ( UXZDataManager* DataManager = UGameInstance::GetSubsystem<UXZDataManager>(GetWorld()->GetGameInstance()) )
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EModularMeshType"), true);
		if ( false == IsValid(EnumPtr) )
		{
			return;
		}

		const FName ModuleTypeName = FName(*EnumPtr->GetNameStringByIndex(static_cast< int32 >( ModuleType )));

		if ( FItemTable_ModuleInfo* ModuleInfo = DataManager->TryGetModuleInfo(ModuleTypeName))
		{
			const int32 rowIndex = ModuleInfo->RowIndex;
			const int32 columnIndex = ModuleInfo->ColumnIndex;

			if ( SlotMaterialInstanceDynamic = UKismetMaterialLibrary::CreateDynamicMaterialInstance(GetWorld(), SlotMaterialInstance) )
			{
				SlotMaterialInstanceDynamic->SetScalarParameterValue(FName("RowIndex"), rowIndex);
				SlotMaterialInstanceDynamic->SetScalarParameterValue(FName("ColumnIndex"), columnIndex);
				PreviewImage->SetBrushFromMaterial(SlotMaterialInstanceDynamic);
			}
		}
	}
}

void UXZModuleSelectSlot::SetCurrentSelectItemID(const int32 NewCurrentIndex)
{
	CurrentIndex = NewCurrentIndex;

	SetModuleImage();
	SetModuleText();
}

void UXZModuleSelectSlot::SetModuleText()
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EModularMeshType"), true);
	
	if ( false == IsValid(EnumPtr) )
	{
		return;
	}

	const FString ModuleTypeName = *EnumPtr->GetNameStringByIndex(static_cast< int32 >( ModuleType )) + FString::FromInt(CurrentIndex + 1);
	
	ModuleName->SetText(FText::FromString(ModuleTypeName));
}

void UXZModuleSelectSlotItem::SetIndex()
{
	if ( UXZDataManager* DataManager = UGameInstance::GetSubsystem<UXZDataManager>(GetWorld()->GetGameInstance()) )
	{
		const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EModularMeshType"), true);
		if ( false == IsValid(EnumPtr) )
		{
			return;
		}

		const FName ModuleTypeName = FName(*EnumPtr->GetNameStringByIndex(static_cast< int32 >( SlotInfo.ModuleType )));

		if ( const FItemTable_ModuleInfo* ModuleInfo = DataManager->TryGetModuleInfo(ModuleTypeName) )
		{
			// 첫 번째 아이템의 ID 설정
			IndexInfo.ItemBaseID = ( ModuleInfo->ID )*1000 + 1;

			const int32 MaxItemsToCheck = 50;

			for ( int32 i = 1; i < MaxItemsToCheck; ++i )
			{
				int32 CurrentModuleID = IndexInfo.ItemBaseID + i;

				if ( const FItemTable_Module* ModuleAsset = DataManager->TryGetModuleAsset(FName(*FString::FromInt(CurrentModuleID))))
				{
					if ( CurrentModuleID / 1000 > ModuleInfo->ID )
					{
						break;
					}

					IndexInfo.ItemLastID = CurrentModuleID;
				}
			}
		}
	}
}
