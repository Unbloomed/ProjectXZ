#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameplayTag/XZGameplayTags.h"
#include "XZModularComponent.generated.h"

UENUM(BlueprintType)
enum class EModularMeshType : uint8
{
	Backpack,
	Vest,
	Helmet,

	Heads,
	Hands,
	Body,
	Belt,
	Pants,
	Foots,
};

class UXZModuleHandlerBase;

UCLASS(ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ))


class PROJECTXZ_API UXZModularComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UXZModularComponent();
	virtual void Attach(EModularMeshType ModuleType, int32 ItemID) ;
	virtual void Dettach(EModularMeshType ModuleType);

protected:
	virtual void InitializeComponent() override;
	virtual void BeginPlay() override;

private:
	int32 GetBaseModuleItemIndex(const int32 ModuleMainID) const;
	FName GetModuleName(const EModularMeshType ModuleType);
	USkeletalMeshComponent* GetSkeletalMeshComponent(EModularMeshType ModuleType) const;

protected:
	UPROPERTY()
	TObjectPtr<class AXZCharacter> Character;

private:
	FSoftObjectPath AssetPath;
};
