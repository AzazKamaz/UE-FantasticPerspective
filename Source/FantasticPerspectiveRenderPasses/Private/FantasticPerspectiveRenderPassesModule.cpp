// Copyright Epic Games, Inc. All Rights Reserved.

#include "Modules/ModuleManager.h"
#include "MovieRenderPipelineDataTypes.h"
#include "MovieRenderPipelineCoreModule.h"
#include "FantasticPerspectiveDeferredPasses.h"

class FFantasticPerspectiveRenderPassesModule : public IModuleInterface
{

	static TSharedRef<MoviePipeline::FMoviePipelineEnginePass> CreateDeferredEnginePass()
	{
		return MakeShared<MoviePipeline::FFantasticPerspectiveDeferredRenderEnginePass>();
	}

	virtual void StartupModule() override
	{
		FMovieRenderPipelineCoreModule* CoreModule = (FMovieRenderPipelineCoreModule*)FModuleManager::Get().LoadModule("MovieRenderPipelineCore");
		if (CoreModule)
		{
			DeferredEnginePassHandle = CoreModule->RegisterEngineRenderPass(FOnCreateEngineRenderPass::CreateStatic(&FFantasticPerspectiveRenderPassesModule::CreateDeferredEnginePass));
		}
	}

	virtual void ShutdownModule() override
	{
		FMovieRenderPipelineCoreModule* CoreModule = (FMovieRenderPipelineCoreModule*)FModuleManager::Get().LoadModule("MovieRenderPipelineCore");
		if (CoreModule)
		{
			CoreModule->UnregisterEngineRenderPass(DeferredEnginePassHandle);
		}

	}
private:

	FDelegateHandle DeferredEnginePassHandle;
};

IMPLEMENT_MODULE(FFantasticPerspectiveRenderPassesModule, FantasticPerspectiveRenderPasses);