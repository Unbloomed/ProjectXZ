#pragma once
#include "CoreMinimal.h"
#include "Components/GameFrameworkInitStateInterface.h"
#include "Components/PawnComponent.h"
#include "XZPawnExtensionComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZPawnExtensionComponent : public UPawnComponent, public IGameFrameworkInitStateInterface
{
	GENERATED_BODY()

public:
	UXZPawnExtensionComponent(const FObjectInitializer& ObjectInitializer);

	//*****************************************************
	//** IGameFrameworkInitStateInterface
	virtual void CheckDefaultInitialization() override;
	//*****************************************************

	void SetupPlayerInputComponent();

	/** Pawn data used to create the pawn. Specified from a spawn function or on a placed instance. */
	//UPROPERTY(EditInstanceOnly, ReplicatedUsing = OnRep_PawnData, Category = "Lyra|Pawn")
	//TObjectPtr<const ULyraPawnData> PawnData;
};
