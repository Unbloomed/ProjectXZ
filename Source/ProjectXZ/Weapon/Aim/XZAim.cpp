#include "Weapon/Aim/XZAim.h"

#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "Character/XZCharacter.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/SpringArmComponent.h"

UXZAim::UXZAim()
{
	Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
}

void UXZAim::Init(AXZAttachment* InWeapon, ACharacter* InOwner, const FAimData& InData)
{
	WeaponAttachment = InWeapon;
	OwnerCharacter = InOwner;
	AimData = InData;

	if (IsValid(AimData.AimCurve) && IsValid(Timeline))
	{
		FOnTimelineFloat TimelineFloat;
		TimelineFloat.BindUFunction(this, "OnAiming");

		Timeline->AddInterpFloat(AimData.AimCurve, TimelineFloat);
		Timeline->SetLooping(false);
		Timeline->SetPlayRate(AimData.AimingSpeed);
	}

	if (AimData.CrosshairWidgetClass)
	{
		APlayerController* PC = Cast<APlayerController>(OwnerCharacter->GetController());

		Crosshair = CreateWidget<UUserWidget>(PC, AimData.CrosshairWidgetClass);
		if (Crosshair)
		{
			Crosshair->AddToViewport();
			Crosshair->SetVisibility(ESlateVisibility::Hidden);
			//Crosshair->UpdateSpreadRange(CurrSpreadRadius, MaxSpreadAlignment);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to create Crosshair widget."));
		}
		//Crosshair->UpdateSpreadRange(CurrSpreadRadius, MaxSpreadAlignment);
	}
}

TObjectPtr<USpringArmComponent> UXZAim::GetXZCharacterSpringArm()
{
	if (CameraSpringArm) return CameraSpringArm;

	CameraSpringArm = Cast<AXZCharacter>(OwnerCharacter)->GetSpringArm();
	return CameraSpringArm;
}

TObjectPtr<UCameraComponent> UXZAim::GetFollowCamera()
{
	if (FollowCamera) return FollowCamera;

	FollowCamera = Cast<AXZCharacter>(OwnerCharacter)->GetFollowCamera();
	return FollowCamera;
}

void UXZAim::StartAiming()
{
	if (IsValid(AimData.AimCurve))
	{
		Timeline->PlayFromStart();

		GetXZCharacterSpringArm()->TargetArmLength = AimData.WeaponZoomData.TargetArmLength;
		GetXZCharacterSpringArm()->SocketOffset = AimData.WeaponZoomData.SocketOffset;
		GetXZCharacterSpringArm()->bEnableCameraLag = AimData.WeaponZoomData.bEnableCameraLag;
	}
}

void UXZAim::EndAiming()
{
	if (IsValid(AimData.AimCurve))
	{
		Timeline->ReverseFromEnd();

		GetXZCharacterSpringArm()->TargetArmLength = AimData.BaseZoomData.TargetArmLength;
		GetXZCharacterSpringArm()->SocketOffset = AimData.BaseZoomData.SocketOffset;
		GetXZCharacterSpringArm()->bEnableCameraLag = AimData.BaseZoomData.bEnableCameraLag;
	}
}

void UXZAim::ShowCrosshair(bool bShowCrosshair)
{
	if (false == IsValid(Crosshair)) return;

	if (bShowCrosshair)
	{
		Crosshair->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Crosshair->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UXZAim::OnAiming(float Output)
{
	GetFollowCamera()->FieldOfView = FMath::Lerp(AimData.WeaponZoomData.FieldOfView, AimData.BaseZoomData.FieldOfView, Output);
}
