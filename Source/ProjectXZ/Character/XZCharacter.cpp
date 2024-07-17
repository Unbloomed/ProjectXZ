#include "XZCharacter.h"

#include "XZCharacterMovementComponent.h"
#include "XZPawnExtensionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

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

	UXZCharacterMovementComponent* LLMoveComp = CastChecked<UXZCharacterMovementComponent>(GetCharacterMovement());
	LLMoveComp->GravityScale = 1.0f;
	LLMoveComp->MaxAcceleration = 2400.0f;
	LLMoveComp->BrakingFrictionFactor = 1.0f;
	LLMoveComp->BrakingFriction = 6.0f;
	LLMoveComp->GroundFriction = 8.0f;
	LLMoveComp->BrakingDecelerationWalking = 1400.0f;
	LLMoveComp->bUseControllerDesiredRotation = false;
	LLMoveComp->bOrientRotationToMovement = false;
	LLMoveComp->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	LLMoveComp->bAllowPhysicsRotationDuringAnimRootMotion = false;
	LLMoveComp->GetNavAgentPropertiesRef().bCanCrouch = true;
	LLMoveComp->bCanWalkOffLedgesWhenCrouching = true;
	LLMoveComp->SetCrouchedHalfHeight(65.0f);

	PawnExtComponent = CreateDefaultSubobject<UXZPawnExtensionComponent>(TEXT("PawnExtensionComponent"));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetRelativeLocation(FVector(-300.0f, 0.0f, 75.0f));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	BaseEyeHeight = 80.0f;
	CrouchedEyeHeight = 50.0f;
}

void AXZCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AXZCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PawnExtComponent->SetupPlayerInputComponent();
}
