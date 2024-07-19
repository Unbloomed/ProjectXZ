#pragma once
#include "CoreMinimal.h"
#include "Styling/SlateStyle.h"

/** 언리얼 에디터 내 Toolbar에 아이콘 형태로 노출
 *
 */

class FWeaponStyle
{
public:
	static void Initialize();
	static void Shutdown();

	/** reloads textures used by slate renderer */
	static void ReloadTextures();

	/** @return The Slate style set for the Shooter game */
	static const ISlateStyle& Get();

	static FName GetStyleSetName();

private:
	static TSharedRef< class FSlateStyleSet > Create();

	static TSharedPtr< class FSlateStyleSet > StyleInstance;
};