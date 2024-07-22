#include "XZCharacter.h"

#include "XZCharacterMovementComponent.h"
#include "XZPawnExtensionComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "ProjectXZ/Component/XZInputComponent.h"

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

	PawnExtComponent = CreateDefaultSubobject<UXZPawnExtensionComponent>(TEXT("PawnExtensionComponent"));

	// Camera
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	CameraSpringArm->SetupAttachment(GetMesh());//Mesh 아래 항목으로 붙인다.
	CameraSpringArm->TargetArmLength = 600.0f;
	CameraSpringArm->bUsePawnControlRotation = true;//true: 마우스를 움직일 때 controller를 따라 SpringArm를 회전시킬 수 있다

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraSpringArm);
	FollowCamera->bUsePawnControlRotation = false;


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
	
	PawnExtComponent->SetupPlayerInputComponent(PlayerInputComponent);
}
