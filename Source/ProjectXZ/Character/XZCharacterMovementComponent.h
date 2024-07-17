#pragma once
#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "XZCharacterMovementComponent.generated.h"

// Information about the ground under the character. It only gets updated as needed.
USTRUCT(BlueprintType)
struct FXZCharacterGroundInfo
{
	GENERATED_BODY()

	FXZCharacterGroundInfo() : LastUpdateFrame(0), GroundDistance(0.0f)
	{}

	uint64 LastUpdateFrame;

	UPROPERTY(BlueprintReadOnly)
	FHitResult GroundHitResult;

	UPROPERTY(BlueprintReadOnly)
	float GroundDistance;
};

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	UXZCharacterMovementComponent(const FObjectInitializer& ObjectInitializer);

	virtual void SimulateMovement(float DeltaTime) override;
	virtual bool CanAttemptJump() const override;
	void SetReplicatedAcceleration(const FVector& InAcceleration);

	// Returns the current ground info.  Calling this will update the ground info if it's out of date.
	UFUNCTION(BlueprintCallable, Category = "Lyra|CharacterMovement")
	const FXZCharacterGroundInfo& GetGroundInfo();


	//*****************************************************
	//** UMovementComponent interface
	virtual FRotator GetDeltaRotation(float DeltaTime) const override;
	virtual float GetMaxSpeed() const override;
	//*****************************************************

protected:
	// Cached ground info for the character.  Do not access this directly!  It's only updated when accessed via GetGroundInfo().
	FXZCharacterGroundInfo CachedGroundInfo;

	UPROPERTY(Transient)
	bool bHasReplicatedAcceleration = false;
};
