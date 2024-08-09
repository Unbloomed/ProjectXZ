#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "XZCharacter.generated.h"

class UXZInventoryComponent;
struct FInputActionValue;
class USpringArmComponent;
class UXZPawnExtensionComponent;
class UXZStatComponent;
class UXZStateComponent;
class UCameraComponent;
class UXZWeaponComponent;
class UTextRenderComponent;
class UObject;
struct FFrame;
class UXZStateComponent;

UENUM()
enum class EXZCharacterType : uint8
{
	eDefault
};

UCLASS()
class PROJECTXZ_API AXZCharacter : public ACharacter, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AXZCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	FORCEINLINE TObjectPtr<UXZWeaponComponent> GetWeaponComponent() const { return WeaponComponent; }
	FORCEINLINE TObjectPtr<UXZStateComponent> GetStateComponent() const { return StateComponent; }
	FORCEINLINE TObjectPtr<UXZStatComponent> GetStatComponent() const { return StatComponent; }
	FORCEINLINE TObjectPtr<UXZInventoryComponent> GetInventoryComponent() const { return InventoryComponent; }
	FORCEINLINE TObjectPtr<UCameraComponent> GetFollowCamera() const { return FollowCamera; }

	void SetUpWidget(class AXZHUD* XZHUD);
	virtual void SetGenericTeamId(const FGenericTeamId& NewTeamID) override;
	virtual FGenericTeamId GetGenericTeamId() const override { return TeamID; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Owner() override;
	virtual void OnRep_PlayerState() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
	void DisablePlayerInput();
	void EnablePlayerInput();
	void SetDead();
	void EndDeadEvent();
	void RespawnPlayer();
	void ResetCharacterData();

private:
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UXZPawnExtensionComponent> PawnExtComponent;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UXZWeaponComponent> WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UXZStatComponent> StatComponent;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UXZStateComponent> StateComponent;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UXZInventoryComponent> InventoryComponent;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Camera", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CameraSpringArm;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Camera", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY()
	APlayerController* PlayerController;

	FTimerHandle RespawnTimerHandle;
	FGenericTeamId TeamID = 0;

	//*****************************************************
	//** 디버깅용. 캐릭터 머리 위에 상태 띄우기.
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Debugging", meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextRender_State;
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Debugging", meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextRender_Weapon;

	FString CurrentCharacterState;
	FString CurrentEquippedWeapon;
	//*****************************************************
};
