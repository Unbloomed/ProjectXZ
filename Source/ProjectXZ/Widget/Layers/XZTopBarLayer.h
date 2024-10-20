// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widget/Base/XZLayerBase.h"
#include "XZTopBarLayer.generated.h"

/**
 * 
 */

class UButton;
class UTextBlock;
class UXZCashSlot;

USTRUCT(BlueprintType)
struct FXZTopBarLayerInfo
{
	GENERATED_BODY()
	UPROPERTY(EditInstanceOnly)
	FString ContentsInformationString;
	UPROPERTY(EditInstanceOnly)
	ESlateVisibility CashSlotVisibility;
};

UCLASS()
class PROJECTXZ_API UXZTopBarLayer : public UXZLayerBase
{
	GENERATED_BODY()
	
public:
		UXZTopBarLayer(const FObjectInitializer& ObjectInitializer);
		virtual void NativeConstruct() override;
		virtual void NativeDestruct() override;

private:
	UFUNCTION()
	void OnCloseButtonClicked();
	UFUNCTION()
	void OnMailButtonClicked();
	UFUNCTION()
	void OnHomeButtonClicked();
	UFUNCTION()
	void OnMenuToggleButtonClicked();

	void OnInitialize();
	void OnUpdate();

private:
	UPROPERTY(EditInstanceOnly, Category = "XZ|Data", Meta = ( AllowPrivateAccess = "true" ))
	struct FXZTopBarLayerInfo TopBarLayerInfo;

	// 1. 뒤로 가기 버튼
	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UButton> CloseButton;

	// 2. 콘텐츠명
	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UTextBlock> ContentsInformationText;

	// 3. 재화표기
	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UXZCashSlot> CashSlot;

	// 4. 우편함 버튼
	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UButton> MailButton;

	// 5. 홈버튼
	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UButton> HomeButton;

	// 6. 햄버거 버튼
	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UButton> MenuToggleButton;

	/*
	1. 뒤로가기 버튼 : UI시스템에 따라 해당 UI를 close 처리한다.
	2. 콘텐츠명 : "인벤토리"스트링키 : "추후기입'
	3. 재화표기 : 강화등의 콘텐츠가 들어가지 않음으로 필요없음	// 재화 표기 슬롯
	4. 우편함 버튼 : 추후구현
	5. 홈버튼 UI시스템에 따라 모든 UI를 close 처리 후 로비로 이동한다.
	6 햄버거 버튼 추후구현
	*/
};
