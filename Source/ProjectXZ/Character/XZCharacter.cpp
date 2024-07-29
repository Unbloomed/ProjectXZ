#include "XZCharacter.h"

#include "XZCharacterMovementComponent.h"
#include "XZPawnExtensionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ProjectXZ/Component/XZInputComponent.h"
#include "ProjectXZ/Component/XZWeaponComponent.h"
#include "Component/XZStateComponent.h"
#include "Component/XZStatComponent.h"
#include "GameplayTag/XZGameplayTags.h"
#include "Manager/XZDataManager.h"

AXZCharacter::AXZCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UXZCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	NetCullDistanceSquared = 900000000.f;

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
	CameraSpringArm->SetupAttachment(GetMesh());//Mesh �Ʒ� �׸����� ���δ�.
	CameraSpringArm->TargetArmLength = 400.0f;
	CameraSpringArm->bUsePawnControlRotation = true;//true: ���콺�� ������ �� controller�� ���� SpringArm�� ȸ����ų �� �ִ�

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
}

void AXZCharacter::DisablePlayerInput()
{
	if (IsLocallyControlled())
	{
		if (APlayerController* ArcadePlayerController = Cast<APlayerController>(GetController()))
		{
			GetCharacterMovement()->Velocity = FVector::ZeroVector; // 이동 벡터 초기화
			GetCharacterMovement()->StopMovementImmediately(); // 이동 중지
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

	// 사격 중이면 중지
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

	// World에서 감추기
	SetActorHiddenInGame(true);

	// Weapon 안보이도록
	// WeaponComponent->SetWeaponHiddenInGame(true);

	if (UXZDataManager* DataManager = UGameInstance::GetSubsystem< UXZDataManager>(GetWorld()->GetGameInstance()))
	{
		if (true == DataManager->IsCharacterStatDataValid())
		{
			FXZCharacterStat CharacterStatData = DataManager->GetCharacterStat(EXZCharacterType::eDefault);
	
			// Respawn Timer
			GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &AXZCharacter::RespawnPlayer, CharacterStatData.RespawnTime, false);
	
			// Respawn Time UI 표시 Timer
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

	// Weapon 안보이도록
	// WeaponComponent->SetWeaponHiddenInGame(true);

	ResetCharacterData();
	SetActorEnableCollision(true);
	EnablePlayerInput();

	// RespawnTimer 중지
	GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
	

	// Spawn 위치 설정
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
	// HP를 Reset한다.
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

}

void AXZCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PawnExtComponent->SetupPlayerInputComponent(PlayerInputComponent);
}
