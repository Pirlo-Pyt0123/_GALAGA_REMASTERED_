// Copyright Epic Games, Inc. All Rights Reserved.
using UnrealBuildTool;

public class GALAGA_REMASTERED : ModuleRules
{
    public GALAGA_REMASTERED(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[]
        {
            "Core",
            "CoreUObject",
            "Engine",
            "InputCore",
            "Niagara",
            "AIModule",
            "UMG",
            "Slate",
            "SlateCore"
        });

        PrivateDependencyModuleNames.AddRange(new string[]
        {
        });
    }
}
