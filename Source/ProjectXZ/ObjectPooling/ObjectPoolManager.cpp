// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectPoolManager.h"

UObjectPoolManager::UObjectPoolManager()
{
}

template <typename T>
void UObjectPoolManager::InitializePool(TSubclassOf<T> ObjectClass, int32 PoolSize)
{
	if (ObjectPools.Contains(ObjectClass))
	{
		// 이미 풀링된 클래스
		return;
	}

	// 오류 사이즈 보정
	if (PooolSize <= 0)
	{
		PoolSize = DefaultPoolSize;
	}

	FObjectPool<T>* NewPool = new FObjectPool<T>();
	NewPool->ObjectClass = ObjectClass;

	ExpandPool(NewPool, ObjectClass, PoolSize);
	/*for (int32 i = 0; i < PoolSize; i++)
	{
		T* New_Object = NewObject<T>(this, ObjectClass);
		New_Object->SetActorHiddenInGame(true);
		NewPool->Pool.Add(New_Object);
	}*/

	ObjectPools.Add(ObjectClass, NewPool);
}

template <typename T>
TObjectPtr<T> UObjectPoolManager::GetPooledObject()
{
	FObjectPool<T>* Pool = static_cast<FObjectPool<T>*>(ObjectPools.FindRef(T::StaticClass()));
	if (!Pool)
	{
		return nullptr;
	}

	if (Pool->Pool.Num() > 0)
	{
		/*T* Object = Pool->Pool.Pop();
		Object->SetActorHiddenInGame(false);
		Pool->ActiveObjects.Add(Object);*/
		return PopPooledObject();
	}
	else
	{
		ExpandPool(Pool, T::StaticClass(), DefaultPoolSize);
		/*T* NewObject = NewObject<T>(this, Pool->ObjectClass);
		NewObject->SetActorHiddenInGame(false);*/
		/*T* Object = Pool->Pool.Pop();
		Object->SetActorHiddenInGame(false);
		Pool->ActiveObjects.Add(Object);*/
		return PopPooledObject();
	}
}

template <typename T>
void UObjectPoolManager::ReturnPooledObject(TObjectPtr<T> Object)
{
	FObjectPool<T>* Pool = static_cast<FObjectPool<T>*>(ObjectPools.FindRef(Object->GetClass()));
	if (!Pool)
	{
		return;
	}

	Object->SetActorHiddenInGame(true);
	Pool->ActiveObjects.Remove(Object);
	Pool->Pool.Add(Object);
}

template<typename T>
void UObjectPoolManager::ExpandPool(FObjectPool<T>* InPool, TSubclassOf<T> InObjectClass, int32 InPoolSize)
{
	for (int32 i = 0; i < InPoolSize; i++)
	{
		T* New_Object = NewObject<T>(this, InObjectClass);
		New_Object->SetActorHiddenInGame(true);
		InPool->Pool.Add(New_Object);
	}
}

template<typename T>
TObjectPtr<T> UObjectPoolManager::PopPooledObject()
{
	TObjectPtr<T> Object = Pool->Pool.Pop();
	Object->SetActorHiddenInGame(false);
	Pool->ActiveObjects.Add(Object);
	return Object;
}
