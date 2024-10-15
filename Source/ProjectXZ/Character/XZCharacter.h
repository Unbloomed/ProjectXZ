#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GenericTeamAgentInterface.h"
#include "Component/XZModularComponent.h"
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
class UXZModularComponent;
class UXZSkeletalMeshComponent;

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

	FORCEINLINE UXZWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }
	FORCEINLINE UXZStateComponent* GetStateComponent() const { return StateComponent; }
	FORCEINLINE UXZStatComponent* GetStatComponent() const { return StatComponent; }
	FORCEINLINE UXZInventoryComponent* GetInventoryComponent() const { return InventoryComponent; }
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return CameraSpringArm; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	FORCEINLINE UXZModularComponent* GetModularComponent() const { return ModularComponent; }
	FORCEINLINE USkeletalMeshComponent* GetSkeletalMeshComponent(EModularMeshType ModuleType) const { return SkeletalMeshComponents[ModuleType]; }

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
	
private:
	void DisablePlayerInput();
	void EnablePlayerInput();
	void SetDead();
	void EndDeadEvent();
	void RespawnPlayer();
	void ResetCharacterData();

private:
	UPROPERTY(EditDefaultsOnly, Category = "XZ|CharacterTypeName", Meta = ( AllowPrivateAccess = "true" ))
	FName CharacterTypeName;

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

	UPROPERTY(EditDefaultsOnly, Category = "XZ|PlayerController", Meta = ( AllowPrivateAccess = "true" ))
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Character", Meta = ( AllowPrivateAccess = "true" ))
	TObjectPtr<UXZModularComponent> ModularComponent;

	FTimerHandle RespawnTimerHandle;

	UPROPERTY(EditAnywhere, Category = "XZ|Team", Meta = ( AllowPrivateAccess = "true" ))
	FGenericTeamId TeamID = 0;

	//*****************************************************
	// SkeletalMeshComponent
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Character", Meta = ( AllowPrivateAccess = "true" ))
	TMap<EModularMeshType, USkeletalMeshComponent*> SkeletalMeshComponents;

	
	//*****************************************************
	//** TextRenderComponent
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Debugging", meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextRender_State;
	UPROPERTY(EditDefaultsOnly, Category = "XZ|Debugging", meta = (AllowPrivateAccess = true))
	TObjectPtr<UTextRenderComponent> TextRender_Weapon;

	FString CurrentCharacterState;
	FString CurrentEquippedWeapon;
	//*****************************************************
};
