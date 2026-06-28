#include "pch.h"
#include "HomePage.xaml.h"
#if __has_include("HomePage.g.cpp")
#include "HomePage.g.cpp"
#endif

#include "AnimationInfo.h"
#include "AnimationService.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::Heyiwei2::implementation {
	void HomePage::test() {
		//auto compositor = ElementCompositionPreview::GetElementVisual(*this).Compositor();
		//auto motionEasing = compositor.CreateCubicBezierEasingFunction({ 0.1f, 0.7f }, { 0.15f, 1.0f });
		//auto fadeEasing = compositor.CreateCubicBezierEasingFunction({ 0.1f, 0.8f }, { 0.15f, 0.95f });

		//ElementCompositionPreview::SetIsTranslationEnabled(WelcomeTextBlock(), true);
		//auto welcomeText = ElementCompositionPreview::GetElementVisual(WelcomeTextBlock());

		//float distance = 60.0f;
		//auto motionAnimation = compositor.CreateScalarKeyFrameAnimation();
		//motionAnimation.InsertKeyFrame(0.0f, distance);
		//motionAnimation.InsertKeyFrame(1.0f, 0.0f, motionEasing);
		//motionAnimation.Duration(std::chrono::milliseconds(1200));

		//auto fadeAnimation = compositor.CreateScalarKeyFrameAnimation();
		//fadeAnimation.InsertKeyFrame(0.0f, 0.0f);
		//fadeAnimation.InsertKeyFrame(1.0f, 1.0f, fadeEasing);
		//fadeAnimation.Duration(std::chrono::milliseconds(1200));

		//welcomeText.StartAnimation(L"Translation.X", motionAnimation);
		//welcomeText.StartAnimation(L"Opacity", fadeAnimation);
		AnimationInfo info;
		AnimationService::GeneralAnimationControl(WelcomeTextBlock(), info);
		info.motionDistanceX = 40.0f;
		AnimationService::GeneralAnimationControl(Welcome2TextBlock(), info);
	};

	void HomePage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		test();
	}
}
