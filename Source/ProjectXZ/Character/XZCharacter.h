#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "XZCharacter.generated.h"

class UXZPawnExtensionComponent;
class UCameraComponent;

UCLASS()
class PROJECTXZ_API AXZCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AXZCharacter(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual void BeginPlay() override;

protected:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XZ|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UXZPawnExtensionComponent> PawnExtComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "XZ|Character", Meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CameraComponent;
};
