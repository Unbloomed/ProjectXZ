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
class UXZStateComponent;

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

	FORCEINLINE TObjectPtr<UXZWeaponComponent> GetWeaponComponent() { return WeaponComponent; }
	FORCEINLINE TObjectPtr<UXZStateComponent> GetStateComponent() { return StateComponent; }
	FORCEINLINE TObjectPtr<UCameraComponent> GetFollowCamera() const { return FollowCamera; }

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
