#pragma once

#include "CoreMinimal.h"
#include "Widget/Base/XZWindowBase.h"
#include "XZInventoryWIndow.generated.h"

class UXZTopBarLayer;
/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZInventoryWindow : public UXZWindowBase
{
	GENERATED_BODY()
	
public:
	UXZInventoryWindow(const FObjectInitializer& ObjectInitializer);
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	private:
		UPROPERTY(meta = ( BindWidget ))
		TObjectPtr< UXZTopBarLayer> TopBarLayer;
};
