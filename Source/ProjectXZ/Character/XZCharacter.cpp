#include "XZCharacter.h"

#include "XZCharacterMovementComponent.h"
#include "XZPawnExtensionComponent.h"
#include "Camera/CameraComponent.h"
#include "Component/XZInventoryComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ProjectXZ/Component/XZInputComponent.h"
#include "ProjectXZ/Component/XZWeaponComponent.h"
#include "Component/XZStateComponent.h"
#include "Component/XZStatComponent.h"
#include "Components/TextRenderComponent.h"
#include "Component/XZModularComponent.h"
#include "GameplayTag/XZGameplayTags.h"
#include "Manager/XZDataManager.h"
#include "Manager/XZSpawnManager.h"
#include "HUD/XZHUD.h"
#include "Widget/XZTimerWidget.h"
#include "ProjectXZ.h"

AXZCharacter::AXZCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UXZCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// TODO: TextRenderCompnet X -> then, change bCanEverTick to false 
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	bReplicates = true;

	NetCullDistanceSquared = 900000000.0f;

	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	checkf(CapsuleComp, TEXT("No CapsuleComp. Check ALLCharacter::ALLCharacter"));
	CapsuleComp->InitCapsuleSize(40.0f, 90.0f);
	//CapsuleComp->SetCollisionProfileName(NAME_LyraCharacterCollisionProfile_Capsule);

	USkeletalMeshComponent* MeshComp = GetMesh();
	checkf(MeshComp, TEXT("No MeshComp. Check ALLCharacter::ALLCharacter"));
	MeshComp->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));  // Rotate mesh to be X forward since it is exported as Y forward.
	//MeshComp->SetCollisionProfileName(NAME_LyraCharacterCollisionProfile_Mesh);

	UXZCharacterMovementComponent* XZMoveComponent = CastChecked<UXZCharacterMovementComponent>(GetCharacterMovement());
	XZMoveComponent->GravityScale = 1.0f;
	XZMoveComponent->MaxAcceleration = 2400.0f;
	XZMoveComponent->BrakingFrictionFactor = 1.0f;
	XZMoveComponent->BrakingFriction = 6.0f;
	XZMoveComponent->GroundFriction = 8.0f;
	XZMoveComponent->BrakingDecelerationWalking = 1400.0f;
	XZMoveComponent->bUseControllerDesiredRotation = false;
	XZMoveComponent->bOrientRotationToMovement = false;
	XZMoveComponent->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	XZMoveComponent->bAllowPhysicsRotationDuringAnimRootMotion = false;
	XZMoveComponent->GetNavAgentPropertiesRef().bCanCrouch = true;
	XZMoveComponent->bCanWalkOffLedgesWhenCrouching = true;
	XZMoveComponent->SetCrouchedHalfHeight(65.0f);
	XZMoveComponent->NavAgentProps.bCanCrouch = true;
	
	PawnExtComponent = CreateDefaultSubobject<UXZPawnExtensionComponent>(TEXT("PawnExtensionComponent"));
	
	// Camera
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(GetMesh());
	CameraSpringArm->TargetArmLength = 300.0f;
	CameraSpringArm->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraSpringArm);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	BaseEyeHeight = 80.0f;
	CrouchedEyeHeight = 50.0f;

	// ModualrComponent
	ModularComponent = CreateDefaultSubobject<UXZModularComponent>(TEXT("ModularComponent"));

	// SkeletalMeshComponent
	HeadMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HeadsMeshComponent"));
	HandsMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HandsMeshComponent"));
	BeltMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BeltMeshComponent"));
	PantsMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PantsMeshComponent"));
	FootsMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FootsMeshComponent"));
	BackpackMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BackpackMeshComponent"));
	VestMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("VestMeshComponent"));
	HelmetMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HelmetMeshComponent"));

	// WeaponComponent
	WeaponComponent = CreateDefaultSubobject<UXZWeaponComponent>(TEXT("WeaponComponent"));

	// StatComponent
	StatComponent = CreateDefaultSubobject<UXZStatComponent>(TEXT("StatComponent"));

	// StateComponent
	StateComponent = CreateDefaultSubobject<UXZStateComponent>(TEXT("StateComponent"));

	// InventoryComponent
	InventoryComponent = CreateDefaultSubobject<UXZInventoryComponent>(TEXT("InventoryComponent"));

	//***********************************************************************************
	//** TextRenderComponent
	TextRender_State = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender_State"));
	TextRender_State->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TextRender_State->SetRelativeLocation(FVector(0.0f, 0.0f, 110.0f));
	TextRender_State->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	
	TextRender_Weapon = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRender_Weapon"));
	TextRender_Weapon->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TextRender_Weapon->SetRelativeLocation(FVector(0.0f, 0.0f, 90.0f));
	TextRender_Weapon->SetRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
	//***********************************************************************************
}

void AXZCharacter::DisablePlayerInput()
{
	if (IsLocallyControlled())
	{
		if (APlayerController* ArcadePlayerController = Cast<APlayerController>(GetController()))
		{
			GetCharacterMovement()->Velocity = FVector::ZeroVector; 
			GetCharacterMovement()->StopMovementImmediately(); 
			ArcadePlayerController->SetIgnoreMoveInput(true);
			ArcadePlayerController->SetIgnoreLookInput(true);
			DisableInput(ArcadePlayerController);
		}
	}
}

void AXZCharacter::EnablePlayerInput()
{
	if (IsLocallyControlled() && GetController())
	{
		if (APlayerController* ArcadePlayerController = Cast<APlayerController>(GetController()))
		{
			EnableInput(ArcadePlayerController);
			ArcadePlayerController->SetIgnoreMoveInput(false);
			ArcadePlayerController->SetIgnoreLookInput(false);
		}
	}
}

void AXZCharacter::SetDead()
{
	ensure(StateComponent);
	ensure(WeaponComponent);
	UE_LOG(LogTemp, Log, TEXT("SetDead"));
	StateComponent->SetState(FXZTags::GetXZTags().StateTag_Dead);

	// if (WeaponComponent)
	// {
	// 	WeaponComponent->EndFire();
	// }

	DisablePlayerInput();

	// DeadAnimation Montage Notify?????????轅붽틓?????????뼿??????嚥싲갭횧????
	EndDeadEvent();
}


// DeadAnimMontage Animation Event
void AXZCharacter::EndDeadEvent()
{
	ensure(StateComponent);
	ensure(WeaponComponent);
	ensure(InventoryComponent);
	UE_LOG(LogTemp, Log, TEXT("EndDeadEvent"));
	GetStateComponent()->SetState(FXZTags::GetXZTags().StateTag_Respawn);

	// WeaponComponent->RemoveAllWeapon();
	// InventoryComponent->Reset();

	SetActorHiddenInGame(true);

	if (UXZDataManager* DataManager = UGameInstance::GetSubsystem< UXZDataManager>(GetWorld()->GetGameInstance()))
	{
		if ( FXZCharacterStat* CharacterStatData = DataManager->TryGetCharacterStat(CharacterTypeName))
		{
			// Respawn Timer
			GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AXZCharacter::RespawnPlayer, CharacterStatData->RespawnTime, false);

			if (APlayerController* PC = Cast<APlayerController>(GetController()) )
			{
				if (AXZHUD* XZHUD = Cast<AXZHUD>(PC->GetHUD())) 
				{
					XZHUD->GetRespawnTimerWidget()->StartTimer(CharacterStatData->RespawnTime);
				}
			}
		}
	}
}


void AXZCharacter::RespawnPlayer()
{
	ensure(StateComponent);
	StateComponent->SetState(FXZTags::GetXZTags().StateTag_Alive_Posture_Idle);

	SetActorHiddenInGame(false);

	// Weapon ????????궰??????猷고?影瑜곸떴??
	// GetInventoryComponent()->ClearAll();

	ResetCharacterData();
	SetActorEnableCollision(true);
	EnablePlayerInput();

	GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
	

	if (UXZSpawnManager* SpawnManager = GetWorld()->GetSubsystem<UXZSpawnManager>())
	{
		SpawnManager->RequestSpawnCharacter( this, GetGenericTeamId());
	}

	GetCharacterMovement()->Velocity = FVector::ZeroVector;

	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		if (AXZHUD* XZHUD = Cast<AXZHUD>(PC->GetHUD()))
		{
			XZHUD->GetRespawnTimerWidget()->StopTimer();
		}
	}
}

void AXZCharacter::ResetCharacterData()
{
	GetStatComponent()->Reset();

	// Weapon Data Rest 
	GetCharacterMovement()->Velocity = FVector::ZeroVector;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AXZCharacter::SetUpWidget(AXZHUD* XZHUD)
{
	if (IsValid(XZHUD)) 
	{
		GetStatComponent()->OnHpChanged.AddUObject(XZHUD, &AXZHUD::UpdateHPBarWidget);
		XZHUD->UpdateHPBarWidget(1.0f, 1.0f);
	}
}


void AXZCharacter::BeginPlay()
{
	Super::BeginPlay();

	TextRender_State->SetVisibility(true);
	TextRender_Weapon->SetVisibility(true);

	GetStatComponent()->OnHpZero.AddUObject(this, &AXZCharacter::SetDead);

	// Test
	SetGenericTeamId(0);

}

void AXZCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurrentCharacterState = GetStateComponent()->GetState().ToString();
	TextRender_State->SetText(FText::FromString(CurrentCharacterState));

	CurrentEquippedWeapon = GetWeaponComponent()->GetEquippedWeaponTag().ToString();
	TextRender_Weapon->SetText(FText::FromString(CurrentEquippedWeapon));
}

void AXZCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Log, TEXT("AXZCharacter::PossessedBy - Do Not Have PlayerController!"));
		return;
	}
}

void AXZCharacter::OnRep_Owner()
{
	PlayerController = Cast<APlayerController>(GetController());
	if (!PlayerController)
	{
		UE_LOG(LogTemp, Log, TEXT("AXZCharacter::OnRep_Owner - Do Not Have PlayerController!"));
		return;
	}

	AActor* OwnerActor = GetOwner();
	if (OwnerActor)
	{
		UE_LOG(LogTemp, Log, TEXT("Owner : %s"), *OwnerActor->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("AXZCharacter::OnRep_Owner - Do Not Have OwnerActor!"));
	}
}

void AXZCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
}

void AXZCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PawnExtComponent->SetupPlayerInputComponent(PlayerInputComponent);
}


void AXZCharacter::SetGenericTeamId(const FGenericTeamId& NewTeamID)
{
	TeamID = NewTeamID;
}
