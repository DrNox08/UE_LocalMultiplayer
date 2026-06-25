// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Demo_Multiplayer : ModuleRules
{
	public Demo_Multiplayer(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"Demo_Multiplayer",
			"Demo_Multiplayer/Variant_Platforming",
			"Demo_Multiplayer/Variant_Platforming/Animation",
			"Demo_Multiplayer/Variant_Combat",
			"Demo_Multiplayer/Variant_Combat/AI",
			"Demo_Multiplayer/Variant_Combat/Animation",
			"Demo_Multiplayer/Variant_Combat/Gameplay",
			"Demo_Multiplayer/Variant_Combat/Interfaces",
			"Demo_Multiplayer/Variant_Combat/UI",
			"Demo_Multiplayer/Variant_SideScrolling",
			"Demo_Multiplayer/Variant_SideScrolling/AI",
			"Demo_Multiplayer/Variant_SideScrolling/Gameplay",
			"Demo_Multiplayer/Variant_SideScrolling/Interfaces",
			"Demo_Multiplayer/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
