// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "Component/XZModularComponent.h"
#include "XZSkeletalMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UXZSkeletalMeshComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
	
public:
	UXZSkeletalMeshComponent() { }
	FORCEINLINE void SetModuleType(const EModularMeshType NewModuleType) { ModuleType = NewModuleType; }
	FORCEINLINE EModularMeshType GetModuleType(EModularMeshType NewModuleType) const { return ModuleType; }

private:
	EModularMeshType ModuleType;
	
};
