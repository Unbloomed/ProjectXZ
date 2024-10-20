#pragma once

#include "CoreMinimal.h"
#include "Widget/Base/XZSlotBase.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "XZItemSlot.generated.h"

/**
 * 
 */


UCLASS()
class PROJECTXZ_API UXZItemSlotItem : public UObject
{
	GENERATED_BODY()
public:
	UXZItemSlotItem() { }
	FORCEINLINE void InitializeData(int32 NewItemID) { ItemID = NewItemID; }
	FORCEINLINE int32 GetItemID() const { return ItemID; }
	FORCEINLINE FGameplayTag GetItemTag() const {return ItemTag; }

private:
	void OnInitialize();
	int32 ItemID;
	FGameplayTag ItemTag;
};


UCLASS()
class PROJECTXZ_API UXZItemSlot : public UXZSlotBase, public IUserObjectListEntry
{
	GENERATED_BODY()
public:
		UXZItemSlot(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	int32 ItemID;
	FGameplayTag ItemTag;
};
