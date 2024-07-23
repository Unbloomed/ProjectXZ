#pragma once
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "XZWeaponComponent.generated.h"

class UXZWeaponData;
class UXZDA_Weapon;
class AXZCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTXZ_API UXZWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UXZWeaponComponent();

	void EquipWeapon1();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
	TMap<FGameplayTag, UXZWeaponData*> Datas; // 무기 목록

	UPROPERTY(EditDefaultsOnly, Category = "DataAsset")
	TArray<UXZDA_Weapon*> Init_Weapons; // 시작 시 가지고 있는 무기 목록

	TObjectPtr<ACharacter> OwnerCharacter;


};
