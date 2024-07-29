#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "XZCharacter.generated.h"

struct FInputActionValue;
class USpringArmComponent;
class UXZPawnExtensionComponent;
class UCameraComponent;
class UXZWeaponComponent;
class UObject;
struct FFrame;

UENUM()
enum class EXZCharacterType : uint8
{
	eDefault
};

UCLASS()
class PROJECTXZ_API AXZCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AXZCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;

	TObjectPtr<UXZWeaponComponent> GetWeaponComponent() { return WeaponComponent; }

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	void DisablePlayerInput();
	void EnablePlayerInput();
	void SetDead();
	void EndDeadEvent();
	// void UpdateRespawnTime();
	void RespawnPlayer();
	void ResetCharacterData();

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XZ|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UXZPawnExtensionComponent> PawnExtComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XZ|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UXZWeaponComponent> WeaponComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XZ|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UXZStatComponent> StatComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XZ|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UXZStateComponent> StateComponent;

	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraSpringArm;

	UPROPERTY(VisibleAnywhere, Category = Camera, Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;


	float RemainingRespawnTime;
	float RespawnTime;
	FTimerHandle RespawnTimerHandle;
};
