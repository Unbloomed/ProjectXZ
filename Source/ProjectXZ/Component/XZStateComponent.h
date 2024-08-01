#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTagContainer.h"
#include "XZStateComponent.generated.h"


DECLARE_MULTICAST_DELEGATE_OneParam(FOnStateChangedDelegate, const FGameplayTag& /*GamePlayTag*/);

class UXZAnimInstance;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTXZ_API UXZStateComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UXZStateComponent();
	void SetState(FGameplayTag NewState);
	FORCEINLINE FGameplayTag GetState() const { return CurrentState; }
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	UFUNCTION()
	void OnRep_CurrentState();
	void OnChangeState();

public:
	FOnStateChangedDelegate OnStateChanged;

protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentState, Transient, VisibleInstanceOnly, Category = State)
	FGameplayTag CurrentState;

	UPROPERTY()
	TObjectPtr<UXZAnimInstance> AnimInstance;
};
