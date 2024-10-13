#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XZItemBase.generated.h"

class UWidgetComponent;
class USphereComponent;

UCLASS()
class PROJECTXZ_API AXZItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AXZItemBase();
	FORCEINLINE const FString& GetItemName() { return ItemName; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, Category = "XZ|Item Properties")
	TObjectPtr<USkeletalMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere, Category = "XZ|Item Properties")
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Item Properties")
	FString ItemName;

	UPROPERTY(EditDefaultsOnly, Category = "XZ|Item Properties")
	int32 ItemID;
};
