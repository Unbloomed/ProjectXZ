#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Character/XZCharacter.h"
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
	FORCEINLINE const FXZCharacterStat& GetCharacterStat() const { return CharacterStat; }
	FORCEINLINE void SetCharacterStat(FXZCharacterStat InCharacterStat) { CharacterStat = InCharacterStat; }
	FORCEINLINE float GetCurrentHp() const { return CurrentHp; }
	float ApplyDamage(float InDamage);
	void Reset();

protected:
	void InitializeComponent() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	FOnHpZeroDelegate OnHpZero;
	FOnHpChangedDelegate OnHpChanged;
	FOnStatChangedDelegate OnStatChanged;

protected:
	void SetHP(float NewHp);

	UFUNCTION()
	void OnRep_CurrentHp();

	UFUNCTION()
	void OnRep_CharacterStat();

protected:
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHp, Transient, VisibleInstanceOnly, Category = Stat)
	float CurrentHp;

	UPROPERTY(Transient, ReplicatedUsing = OnRep_CharacterStat, VisibleInstanceOnly, Category = Stat, Meta = (AllowPrivateAccess = "true"))
	FXZCharacterStat CharacterStat;
};
