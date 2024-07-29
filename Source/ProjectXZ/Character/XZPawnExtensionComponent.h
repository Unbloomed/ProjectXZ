#pragma once
#include "CoreMinimal.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "XZPawnExtensionComponent.generated.h"

class AXZCharacter;
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
	TObjectPtr<AXZCharacter> GetXZCharacter();

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
	void Input_LookMouse(const FInputActionValue& InputActionValue);
	void Input_Crouch(const FInputActionValue& InputActionValue);

	void Input_EquipSlot1(const FInputActionValue& InputActionValue);
	void Input_EquipSlot2(const FInputActionValue& InputActionValue);

	void Input_WeaponFire(const FInputActionValue& InputActionValue);
	void Input_WeaponReload(const FInputActionValue& InputActionValue);

	void Input_Jump(FGameplayTag InputTag);
	void Input_StopJumping(FGameplayTag InputTag);
	void Input_Aim(FGameplayTag InputTag);
	void Input_StopAiming(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UInputMappingContext> DefaultIMC;

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = true))
	TObjectPtr<UXZDA_InputConfig> InputConfig;


	UPROPERTY()
	TObjectPtr<AXZCharacter> XZCharacter;
};
