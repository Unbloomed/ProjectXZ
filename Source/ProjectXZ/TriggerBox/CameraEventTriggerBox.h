// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "CameraEventTriggerBox.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTXZ_API ACameraEventTriggerBox : public ATriggerBox
{
	GENERATED_BODY()
public:
	ACameraEventTriggerBox();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnActorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(EditAnywhere, Category = "XZ|Camera", Meta = ( AllowPrivateAccess = "true" ))
	TObjectPtr< ACameraActor> Camera;
};
