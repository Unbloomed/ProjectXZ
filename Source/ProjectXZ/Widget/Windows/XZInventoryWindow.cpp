
#include "XZInventoryWindow.h"
#include "GameplayTag/XZGameplayTags.h"


UXZInventoryWindow::UXZInventoryWindow(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	WindowType = FXZTags::GetXZTags().Widget_UIType_FullUI;
	UITag = FGameplayTag::RequestGameplayTag(FName("UI.Window.InventoryWindow"));
}

void UXZInventoryWindow::NativeConstruct()
{
	Super::NativeConstruct();
}

void UXZInventoryWindow::NativeDestruct()
{
	Super::NativeDestruct();
}
