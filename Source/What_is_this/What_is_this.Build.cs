// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class What_is_this : ModuleRules
{
	public What_is_this(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"UMG"
		});
	}
}
