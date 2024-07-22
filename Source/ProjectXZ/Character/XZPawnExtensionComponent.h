#pragma once
#include "CoreMinimal.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "XZPawnExtensionComponent.generated.h"

struct FInputActionValue;
class UXZDA_InputConfig;
class UInputAction;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZPawnExtensionComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:
	UXZPawnExtensionComponent(const FObjectInitializer& ObjectInitializer);

	//*****************************************************
	//** IGameFrameworkInitStateInterface
	virtual void CheckDefaultInitialization() override;
	//*****************************************************

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	/** Pawn data used to create the pawn. Specified from a spawn function or on a placed instance. */
	//UPROPERTY(EditInstanceOnly, ReplicatedUsing = OnRep_PawnData, Category = "Lyra|Pawn")
	//TObjectPtr<const ULyraPawnData> PawnData;

private:
	void Input_Move(const FInputActionValue& InputActionValue);
	void Input_Crouch(const FInputActionValue& InputActionValue);

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> DefaultIMC;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UXZDA_InputConfig> InputConfig;
};
