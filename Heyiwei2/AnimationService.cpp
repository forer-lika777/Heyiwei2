#include "pch.h"
#include "AnimationService.h"

#include <winrt/Microsoft.UI.Xaml.Hosting.h>

using CompositionAnimation = winrt::Windows::UI::Composition::CompositionAnimation;
using Compositor = winrt::Microsoft::UI::Composition::Compositor;
using namespace winrt::Microsoft::UI::Xaml::Hosting;

void AnimationService::GeneralAnimationControl(winrt::Microsoft::UI::Xaml::UIElement const& element, AnimationInfo const& animationInfo) {
	auto compositor = ElementCompositionPreview::GetElementVisual(element).Compositor();
	auto motionEasing = compositor.CreateCubicBezierEasingFunction({ 0.1f, 0.7f }, { 0.15f, 1.0f });
	auto fadeEasing = compositor.CreateCubicBezierEasingFunction({ 0.1f, 0.8f }, { 0.15f, 0.95f });

	ElementCompositionPreview::SetIsTranslationEnabled(element, true);
	auto visual = ElementCompositionPreview::GetElementVisual(element);

	auto motionXAnimation = compositor.CreateScalarKeyFrameAnimation();
	motionXAnimation.InsertKeyFrame(0.0f, animationInfo.motionDistanceX);
	motionXAnimation.InsertKeyFrame(1.0f, 0.0f, motionEasing);
	motionXAnimation.Duration(std::chrono::milliseconds(1200));

	auto motionYAnimation = compositor.CreateScalarKeyFrameAnimation();
	motionYAnimation.InsertKeyFrame(0.0f, animationInfo.motionDistanceY);
	motionYAnimation.InsertKeyFrame(1.0f, 0.0f, motionEasing);
	motionYAnimation.Duration(std::chrono::milliseconds(1200));

	auto fadeAnimation = compositor.CreateScalarKeyFrameAnimation();
	fadeAnimation.InsertKeyFrame(0.0f, 0.0f);
	fadeAnimation.InsertKeyFrame(1.0f, 1.0f, fadeEasing);
	fadeAnimation.Duration(std::chrono::milliseconds(1200));

	visual.StartAnimation(L"Translation.X", motionXAnimation);
	visual.StartAnimation(L"Translation.Y", motionYAnimation);
	visual.StartAnimation(L"Opacity", fadeAnimation);
}