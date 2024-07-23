#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "XZAttachment.generated.h"

UCLASS()
class PROJECTXZ_API AXZAttachment : public AActor
{
	GENERATED_BODY()
	
public:	
	AXZAttachment();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USceneComponent> Root;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UStaticMesh> Mesh;
	

};
