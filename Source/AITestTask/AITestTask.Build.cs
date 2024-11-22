// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class AITestTask : ModuleRules
{
	public AITestTask(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
