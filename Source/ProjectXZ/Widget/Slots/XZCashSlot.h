#pragma once

#include "CoreMinimal.h"
#include "Widget/Base/XZSlotBase.h"
#include "XZCashSlot.generated.h"

class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZCashSlot : public UXZSlotBase
{
	GENERATED_BODY()
	
	public:
		UXZCashSlot(const FObjectInitializer& ObjectInitializer);


private:
	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UImage> CashImage;

	UPROPERTY(meta = ( BindWidget ))
	TObjectPtr<UTextBlock> CashAmountText;

	int32 CashAmount;

};
