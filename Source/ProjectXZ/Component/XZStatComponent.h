#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/XZCharacter.h"
#include "GameplayTagContainer.h"
#include "XZStatComponent.generated.h"

// Header 
USTRUCT(BlueprintType)
struct FXZCharacterStat : public FTableRowBase
{
	GENERATED_BODY()

public:
	FXZCharacterStat() 
		: CharacterType(EXZCharacterType::eDefault), MaxHp(0.0f), ShootRange(0.0f), MovementSpeed(0.0f) {  }

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	EXZCharacterType CharacterType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MaxHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float ShootRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float MovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stat)
	float RespawnTime;
};

DECLARE_MULTICAST_DELEGATE(FOnHpZeroDelegate);
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHpChangedDelegate, float /*CurrentHp*/, float /*MaxHp*/);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnStatChangedDelegate, const FXZCharacterStat& /*BaseStat*/);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTXZ_API UXZStatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UXZStatComponent();

public:
	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	
	void SetCharacterTypeName(const FName NewCharacterTypeName) { CharacterTypeName = NewCharacterTypeName; }

	float ApplyDamage(float InDamage);
	void IncreaseHealth(float Amount);
	void DecreaseHealth(float Amount);
	void Reset();

protected:
	void InitializeComponent() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void BeginPlay() override;

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;
	FOnStatChangedDelegate OnStatChanged;

private:
	void SetHP(float NewHp);

	UFUNCTION()
	void OnRep_CurrentHp();

protected:
	UPROPERTY(Transient, BlueprintReadWrite, Category = "XZ|CharacterTypeName", Meta = ( AllowPrivateAccess = "true" ))
	FName CharacterTypeName;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentHp, Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(Transient,  VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	float MaxHp = 0.f;
};
