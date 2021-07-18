// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "MoviePipelineDeferredPasses.h"
#include "FantasticPerspectiveDeferredPasses.generated.h"

class UTextureRenderTarget2D;
struct FImageOverlappedAccumulator;
class FSceneViewFamily;
class FSceneView;

UCLASS(BlueprintType)
class FANTASTICPERSPECTIVERENDERPASSES_API UFantasticPerspectiveDeferredPassBase : public UMoviePipelineRenderPass
{
	GENERATED_BODY()

protected:

	// UMoviePipelineRenderPass API
	virtual void GetRequiredEnginePassesImpl(TSet<FMoviePipelinePassIdentifier>& RequiredEnginePasses) override;
	virtual void GatherOutputPassesImpl(TArray<FMoviePipelinePassIdentifier>& ExpectedRenderPasses) override;
	virtual void SetupImpl(TArray<TSharedPtr<MoviePipeline::FMoviePipelineEnginePass>>& InEnginePasses, const MoviePipeline::FMoviePipelineRenderPassInitSettings& InPassInitSettings) override;
	// ~UMovieRenderPassAPI

	virtual FText GetDisplayText() const override { return FText::Format(FText::FromString("Fantastic Perspective {0}"), NSLOCTEXT("MovieRenderPipeline", "DeferredBasePassSettingDisplayName", "Deferred Rendering")); }


	void OnBackbufferSampleReady(TArray<FFloat16Color>& InPixelData, FMoviePipelineRenderPassMetrics InSampleState);
	void OnSetupView(FSceneViewFamily& InViewFamily, FSceneView& InView, const FMoviePipelineRenderPassMetrics& InSampleState);

private:
	/** List of passes by name that we should output. */
	TArray<FString> DesiredOutputPasses;

	bool bAccumulateAlpha;

	/** One accumulator per sample source being saved. */
	TArray<TSharedPtr<FImageOverlappedAccumulator, ESPMode::ThreadSafe>> ImageTileAccumulator;
};

DECLARE_MULTICAST_DELEGATE_ThreeParams(FMoviePipelineSetupView, FSceneViewFamily&, FSceneView&, const FMoviePipelineRenderPassMetrics&);

namespace MoviePipeline
{
	struct FFantasticPerspectiveDeferredRenderEnginePass : public FMoviePipelineEnginePass, FGCObject
	{
		FFantasticPerspectiveDeferredRenderEnginePass()
			: FMoviePipelineEnginePass(FMoviePipelinePassIdentifier(TEXT("MainFantasticPerspectiveDeferredPass")))
		{
		}

		virtual void Setup(TWeakObjectPtr<UMoviePipeline> InOwningPipeline, const FMoviePipelineRenderPassInitSettings& InInitSettings) override;
		virtual void RenderSample_GameThread(const FMoviePipelineRenderPassMetrics& InSampleState) override;
		virtual void Teardown() override;

		// FGCObject Interface
		virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
		// ~FGCObject Interface

		FMoviePipelineSampleReady BackbufferReadyDelegate;
		FMoviePipelineSetupView SetupViewDelegate;

	protected:
		FSceneView* CalcSceneView(FSceneViewFamily* ViewFamily, const FMoviePipelineRenderPassMetrics& InSampleState);
		void ApplyFantasticPerspective(FSceneViewProjectionData& ProjectionData);

	protected:
		FSceneViewStateReference ViewState;

		/** A queue of surfaces that the render targets can be copied to. If no surface is available the game thread should hold off on submitting more samples. */
		TSharedPtr<FMoviePipelineSurfaceQueue> SurfaceQueue;

		TWeakObjectPtr<UTextureRenderTarget2D> TileRenderTarget;
	};
}