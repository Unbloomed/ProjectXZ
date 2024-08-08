#pragma once
#include "CoreMinimal.h"
#include "Weapon/WeaponLibrary.h"
#include "XZAim.generated.h"

class USpringArmComponent;
class UCameraComponent;

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZAim : public UObject
{
	GENERATED_BODY()

public:
	UXZAim();

	void Init(class AXZAttachment* InWeapon, ACharacter* InOwner, const FAimData& InData);
	TObjectPtr<USpringArmComponent> GetXZCharacterSpringArm();
	TObjectPtr<UCameraComponent> GetFollowCamera();

	void StartAiming();
	void EndAiming();

	void ShowCrosshair(bool bShowCrosshair);

private:
	void OnAiming(float Output);

	TObjectPtr<AXZAttachment> WeaponAttachment;
	ACharacter* OwnerCharacter;
	FAimData AimData;

	TObjectPtr<USpringArmComponent> CameraSpringArm;
	TObjectPtr<UCameraComponent> FollowCamera;
	TObjectPtr<UUserWidget> Crosshair;

	UPROPERTY()
	TObjectPtr<UTimelineComponent> Timeline;
};
