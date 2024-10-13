#include "XZStatComponent.h"
#include "Net/UnrealNetwork.h"
#include "Manager/XZDataManager.h"
#include "GameplayTag/XZGameplayTags.h"

UXZStatComponent::UXZStatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;

	// 블루프린트에서 안들어감
	CharacterTypeName = TEXT("DefaultCharacter");
	// TeamTag = FXZTags::GetXZTags().GameTeamTag_None;
}

void UXZStatComponent::InitializeComponent()
{
	Super::InitializeComponent();
	
	SetIsReplicated(true);

	// DataManger
	if (UXZDataManager* DataManager = UGameInstance::GetSubsystem<UXZDataManager>(GetWorld()->GetGameInstance()))
	{
		if ( FXZCharacterStat* CharacterStatData = DataManager->TryGetCharacterStat(CharacterTypeName))
		{
			MaxHp = CharacterStatData->MaxHp;
		}
	}
	
	Reset();
}

void UXZStatComponent::Reset()
{
	SetHP(MaxHp);
}

void UXZStatComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UXZStatComponent, CurrentHp);
}

void UXZStatComponent::BeginPlay()
{
	Super::BeginPlay();

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
	CurrentHp = FMath::Clamp<float>(NewHp, 0.f, MaxHp);
	if (NewHp == 0) 
	{
		bool bk = false;
		bk = true;
	}
	UE_LOG(LogTemp, Log, TEXT(" CurrentHp : [%f]"), CurrentHp);

	if (OnHpChanged.IsBound())
	{
		OnHpChanged.Broadcast(NewHp, MaxHp);
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
		OnHpChanged.Broadcast(CurrentHp, MaxHp);
	}
	if (CurrentHp <= 0.0f)
	{
		OnHpZero.Broadcast();
	}
}
