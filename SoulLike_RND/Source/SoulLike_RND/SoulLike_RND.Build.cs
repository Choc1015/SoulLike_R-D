// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SoulLike_RND : ModuleRules
{
	public SoulLike_RND(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
