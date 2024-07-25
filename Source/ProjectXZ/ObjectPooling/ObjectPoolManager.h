// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ObjectPoolManager.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API UObjectPoolManager : public UObject
{
	GENERATED_BODY()
	
public:
	UObjectPoolManager();

	template <typename T>
	void InitializePool(TSubclassOf<T> InObjectClass, int32 InPoolSize);

	template <typename T>
	TObjectPtr<T> GetPooledObject();

	template <typename T>
	void ReturnPooledObject(TObjectPtr<T> InObject);

private:

	template <typename T>
	struct FObjectPool
	{
		TSubclassOf<T> ObjectClass;
		TArray<TObjectPtr<T>> Pool;
		TArray<TObjectPtr<T>> ActiveObjects;
	};

	template <typename T>
	void ExpandPool(FObjectPool<T>* InPool, TSubclassOf<T> InObjectClass, int32 InPoolSize);

	template <typename T>
	TObjectPtr<T> PopPooledObject();

	UPROPERTY()
	TMap<TSubclassOf<UObject>, void*> ObjectPools;

	UPROPERTY()
	int32 DefaultPoolSize = 10;
};
