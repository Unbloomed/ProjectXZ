#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XZMagazine.generated.h"

UCLASS()
class PROJECTXZ_API AXZMagazine : public AActor
{
	GENERATED_BODY()
	
public:	
	AXZMagazine();
	void SetEject();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh_Full;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> Mesh_Empty;

private:
	uint8 bEject : 1;
};
