#include "Weapon/Magazine/XZMagazine.h"

AXZMagazine::AXZMagazine()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Mesh_Full = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Full"));
	Mesh_Full->SetupAttachment(Root);
	Mesh_Empty = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh_Empty"));
	Mesh_Empty->SetupAttachment(Root);
}

void AXZMagazine::BeginPlay()
{
	Super::BeginPlay();

	if (false == bEject)
	{
		Mesh_Full->SetVisibility(true); // �Ѿ��� ����ִ� źâ ����
	}
}

void AXZMagazine::SetEject()
{
	bEject = true;

	Mesh_Full->SetVisibility(false);
	Mesh_Empty->SetSimulatePhysics(true);
}
