#pragma once

#include "HomePage.g.h"

namespace winrt::Heyiwei2::implementation {
	struct HomePage : HomePageT<HomePage> {
		HomePage() {}

		void test();
		void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
	};
}

namespace winrt::Heyiwei2::factory_implementation {
	struct HomePage : HomePageT<HomePage, implementation::HomePage> {};
}
