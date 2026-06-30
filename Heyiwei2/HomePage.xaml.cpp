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
	void HomePage::playEntryAnimation() {
		AnimationInfo info;
		AnimationService::GeneralAnimationControl(WelcomeTextBlock(), info);
		info.motionDistanceX = 40.0f;
		AnimationService::GeneralAnimationControl(Welcome2TextBlock(), info);
	};

	void HomePage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		playEntryAnimation();
	}
}
