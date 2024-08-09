// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ProjectXZ : ModuleRules
{
	public ProjectXZ(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicIncludePaths.AddRange(new string[] { "ProjectXZ" });
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags", "UMG" , "GameplayTasks", "AIModule", "Slate", "SlateCore" });
	}
}
