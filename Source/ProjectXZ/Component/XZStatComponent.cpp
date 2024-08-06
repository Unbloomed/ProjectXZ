#include "XZStatComponent.h"
#include "Net/UnrealNetwork.h"
#include "Manager/XZDataManager.h"
#include "MVVMSubsystem.h"

UXZStatComponent::UXZStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
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
	SetHP(CurrentHp - Amount);
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
