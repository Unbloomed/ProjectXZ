// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Base/XZLayerBase.h"
#include "Component/XZModularComponent.h"
#include "XZEquipLayer.generated.h"


class UImage;
class UListView;


USTRUCT(BlueprintType)
struct  FXZEquipmentSlotInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	EModularMeshType ModuleType;
};

USTRUCT(BlueprintType)
struct  FXZItemSlotInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	int32 ItemID;
};

UCLASS()
class PROJECTXZ_API UXZEquipLayer : public UXZLayerBase
{
	GENERATED_BODY()
public:
	UXZEquipLayer(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	// 캐릭터 이미지 (렌더타겟이든 뭐든)
	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UImage> CharacterImage;
	
	// 장비 레이어
	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UListView> EquipListView;

	// 총 레이어 (총, 파츠)
	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UListView> GunListView;

	// 소비 아이템 레이어
	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UListView> ConsumableListView;

	UPROPERTY(EditDefaultsOnly)
	TArray<FXZEquipmentSlotInfo> EquipmentSlotInfo;
	/*
	TObjectPtr<UGunSlot> 
	*/
	
};
