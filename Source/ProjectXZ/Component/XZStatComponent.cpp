#include "XZStatComponent.h"
#include "Net/UnrealNetwork.h"
#include "Manager/XZDataManager.h"
#include "GameplayTag/XZGameplayTags.h"

UXZStatComponent::UXZStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	// TeamTag = FXZTags::GetXZTags().GameTeamTag_None;
}

void UXZStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	SetIsReplicated(true);
	// DataManger
	if (UXZDataManager* DataManager = UGameInstance::GetSubsystem<UXZDataManager>(GetWorld()->GetGameInstance()))
	{
		if (DataManager->IsCharacterStatDataValid()) 
		{
			FXZCharacterStat CharacterStatData = DataManager->GetCharacterStat(EXZCharacterType::eDefault);
			CharacterStat = CharacterStatData;

			SetHP(CharacterStatData.MaxHp);
			UE_LOG(LogTemp, Log, TEXT("CharacterStatData.MaxHp : [%f]"), CharacterStatData.MaxHp);
		}
	}
	
	Reset();
}

void UXZStatComponent::Reset()
{
	SetHP(CharacterStat.MaxHp);
}

void UXZStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UXZStatComponent, CurrentHp);
	DOREPLIFETIME_CONDITION(UXZStatComponent, CharacterStat, COND_OwnerOnly);
}

float UXZStatComponent::ApplyDamage(float InDamage)
{
	const float PrevHp = CurrentHp;
	const float ActualDamage = FMath::Clamp<float>(InDamage, 0.0f, InDamage);
	
	SetHP(PrevHp - ActualDamage);

	// UE_LOG(LogTemp, Log, TEXT("InDamage : [%f] / PrevHp : [%f] / CurrentHp : [%f]"), InDamage,PrevHp, CurrentHp);

	if (CurrentHp <= KINDA_SMALL_NUMBER)
	{
		if (OnHpZero.IsBound())
		{
			OnHpZero.Broadcast();
		}
	}
	return ActualDamage;
}

void UXZStatComponent::SetHP(float NewHp)
{
	CurrentHp = FMath::Clamp<float>(NewHp, 0.f, CharacterStat.MaxHp);
	if (NewHp == 0) 
	{
		bool bk = false;
		bk = true;
	}
	UE_LOG(LogTemp, Log, TEXT(" CurrentHp : [%f]"), CurrentHp);

	if (OnHpChanged.IsBound())
	{
		OnHpChanged.Broadcast(NewHp, CharacterStat.MaxHp);
	}
}

void UXZStatComponent::IncreaseHealth(float Amount)
{
	SetHP(CurrentHp + Amount);
}

void UXZStatComponent::DecreaseHealth(float Amount)
{
	ApplyDamage(Amount);
}

void UXZStatComponent::OnRep_CurrentHp()
{
	if (OnHpChanged.IsBound())
	{
		OnHpChanged.Broadcast(CurrentHp, CharacterStat.MaxHp);
	}
	if (CurrentHp <= 0.0f)
	{
		OnHpZero.Broadcast();
	}
}

void UXZStatComponent::OnRep_CharacterStat()
{
	if (OnStatChanged.IsBound())
	{
		OnStatChanged.Broadcast(CharacterStat);
	}
}
