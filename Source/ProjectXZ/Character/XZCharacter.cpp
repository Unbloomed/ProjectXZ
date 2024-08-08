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
#include "GameplayTag/XZGameplayTags.h"
#include "Manager/XZDataManager.h"

AXZCharacter::AXZCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UXZCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	// TODO: Ä³¸¯ÅÍ ¸Ó¸® À§ µð¹ö±ë¿ë ÅØ½ºÆ® ¶§¹®¿¡ Æ½ ´ç ºÁ¾ßÇØ¼­ true¼³Á¤. ÃßÈÄ¿¡ false·Î º¯°æ.
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
	CameraSpringArm->SetupAttachment(GetMesh());//Mesh ï¿½Æ·ï¿½ ï¿½×¸ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ï¿½Î´ï¿½.
	CameraSpringArm->TargetArmLength = 300.0f;
	CameraSpringArm->bUsePawnControlRotation = true;//true: ï¿½ï¿½ï¿½ì½ºï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ ï¿½ï¿½ controllerï¿½ï¿½ ï¿½ï¿½ï¿½ï¿½ SpringArmï¿½ï¿½ È¸ï¿½ï¿½ï¿½ï¿½Å³ ï¿½ï¿½ ï¿½Ö´ï¿½

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraSpringArm);
	FollowCamera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	BaseEyeHeight = 80.0f;
	CrouchedEyeHeight = 50.0f;

	// WeaponComponent
	WeaponComponent = CreateDefaultSubobject<UXZWeaponComponent>(TEXT("WeaponComponent"));

	// StatComponent
	StatComponent = CreateDefaultSubobject<UXZStatComponent>(TEXT("StatComponent"));

	// StateComponent
	StateComponent = CreateDefaultSubobject<UXZStateComponent>(TEXT("StateComponent"));

	// InventoryComponent
	InventoryComponent = CreateDefaultSubobject<UXZInventoryComponent>(TEXT("InventoryComponent"));


	//***********************************************************************************
	//** µð¹ö±ë¿ë. Ä³¸¯ÅÍ ¸Ó¸® À§¿¡ »óÅÂ ¶ç¿ì±â.
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
			GetCharacterMovement()->Velocity = FVector::ZeroVector; // ?´ë™ ë²¡í„° ì´ˆê¸°??
			GetCharacterMovement()->StopMovementImmediately(); // ?´ë™ ì¤‘ì?
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
	if (StateComponent) 
	{
		StateComponent->SetState(FXZTags::GetXZTags().StateTag_Dead);
	}

	if (UXZDataManager* DataManager = UGameInstance::GetSubsystem<UXZDataManager>(GetWorld()->GetGameInstance()))
	{
		if (true == DataManager->IsCharacterStatDataValid())
		{
			FXZCharacterStat CharacterStatData = DataManager->GetCharacterStat(EXZCharacterType::eDefault);
			RespawnTime = CharacterStatData.RespawnTime;
			RemainingRespawnTime = RespawnTime;
			
		}
	}

	// ?¬ê²© ì¤‘ì´ë©?ì¤‘ì?
	// if (WeaponComponent)
	// {
	// 	WeaponComponent->EndFire();
	// }

	DisablePlayerInput();
}


// DeadAnimMontage Animation Event
void AXZCharacter::EndDeadEvent()
{
	if (StateComponent)
	{
		StateComponent->SetState(FXZTags::GetXZTags().StateTag_Respawn);
	}

	// World?ì„œ ê°ì¶”ê¸?
	SetActorHiddenInGame(true);

	// Weapon ?ˆë³´?´ë„ë¡?
	// WeaponComponent->SetWeaponHiddenInGame(true);

	if (UXZDataManager* DataManager = UGameInstance::GetSubsystem< UXZDataManager>(GetWorld()->GetGameInstance()))
	{
		if (true == DataManager->IsCharacterStatDataValid())
		{
			FXZCharacterStat CharacterStatData = DataManager->GetCharacterStat(EXZCharacterType::eDefault);
	
			// Respawn Timer
			GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AXZCharacter::RespawnPlayer, CharacterStatData.RespawnTime, false);
	
			// Respawn Time UI ?œì‹œ Timer
			// GetWorld()->GetTimerManager().SetTimer(UpdateTimerHandle, this, &AXZCharacter::UpdateRespawnTime, CharacterRespawnData.RespawnTimerRate, true);
		}
	}
}

void AXZCharacter::RespawnPlayer()
{
	if (StateComponent)
	{
		StateComponent->SetState(FXZTags::GetXZTags().StateTag_Alive_Posture_Idle);
	}

	SetActorHiddenInGame(false);

	// Weapon ?ˆë³´?´ë„ë¡?
	// WeaponComponent->SetWeaponHiddenInGame(true);

	ResetCharacterData();
	SetActorEnableCollision(true);
	EnablePlayerInput();

	// RespawnTimer ì¤‘ì?
	GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
	

	// Spawn ?„ì¹˜ ?¤ì •
	// if (UACSpawnManager* SpawnManager = GetWorld()->GetSubsystem<UACSpawnManager>())
	// {
	// 	if (AACGameState* ArcadeGameState = Cast<AACGameState>(UGameplayStatics::GetGameState(GetWorld())))
	// 	{
	// 		SpawnManager->RequestRespawnCharacter(this, ArcadeGameState->GetCurrentGamePhase());
	// 	}
	// }

	GetCharacterMovement()->Velocity = FVector::ZeroVector;
}

void AXZCharacter::ResetCharacterData()
{
	// HPë¥?Reset?œë‹¤.
	StatComponent->Reset();

	// Weapon Data Rest 
	// WeaponComponent->Reset();

	GetCharacterMovement()->Velocity = FVector::ZeroVector;
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_None);
	GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
}

void AXZCharacter::BeginPlay()
{
	Super::BeginPlay();

	// µð¹ö±ë¿ë.
	TextRender_State->SetVisibility(true);
	TextRender_Weapon->SetVisibility(true);
}

void AXZCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	// µð¹ö±ë¿ë.
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
