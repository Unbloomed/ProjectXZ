#include "XZDA_Weapon.h"

UXZDA_Weapon::UXZDA_Weapon()
{
	AttachmentClass = AActor::StaticClass();
}

void UXZDA_Weapon::BeginPlay(ACharacter* InOwner, UCWeaponData** OutWeaponData)
{
}
