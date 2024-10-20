#pragma once

#include "CoreMinimal.h"
#include "Widget/Base/XZLayerBase.h"
#include "Component/XZModularComponent.h"
#include "XZModuleCustomizingLayer.generated.h"

class UXZModuleSelectSlot;

/*
ListView에 담긴 Slot의 정보
*/
class UListView;

USTRUCT(BlueprintType)
struct FXZModuleSelectSlotInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly)
	EModularMeshType ModuleType;
};

UCLASS()
class PROJECTXZ_API UXZModuleCustomizingLayer : public UXZLayerBase
{
	GENERATED_BODY()
	
	public:
		UXZModuleCustomizingLayer(const FObjectInitializer& ObjectInitializer);
		virtual void NativeConstruct() override;

	private:
		UPROPERTY(EditDefaultsOnly)
		TArray<FXZModuleSelectSlotInfo> SelectSlotsInfo;

		UPROPERTY(meta = ( BindWidget ))
		TObjectPtr<UListView> SlotListView;
};
