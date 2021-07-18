// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FantasticPerspectiveRenderPasses : ModuleRules
{
	public FantasticPerspectiveRenderPasses(ReadOnlyTargetRules Target) : base(Target)
	{
		PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"Engine",
				"ImageWriteQueue",
				"MovieRenderPipelineCore",
				"FantasticPerspectivePlugin"
			}
		);

		PublicDependencyModuleNames.AddRange(
			new string[] {
				"MovieRenderPipelineRenderPasses",
				"RenderCore",
				"RHI",
			}
		);
	}
}
