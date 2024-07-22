#include "XZAttachment.h"
#include "GameFramework/Character.h"

AXZAttachment::AXZAttachment()
{
	//Root = CreateDefaultSubobject<AXZAttachment>(FName(TEXT("Root")));
}

void AXZAttachment::BeginPlay()
{
	Super::BeginPlay();

	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());

	//TArray<USceneComponent*> Children;
	//Root->GetChildrenComponents(true, Children);
	//for (USceneComponent* child : Children)
	//{
	//	//UShape
	//}
	
}

// Called every frame
void AXZAttachment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

