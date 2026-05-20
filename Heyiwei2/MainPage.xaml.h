#pragma once

#include "MainPage.g.h"
#include "MainManager.h"

namespace winrt::Heyiwei2::implementation {
	struct MainPage : MainPageT<MainPage> {
	private:
		void openHomePage();
		void openDormListPage();
	public:
		MainPage();

		void Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
		void NavigationView_Invoked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args);

		hstring currentPage;
	};
}

namespace winrt::Heyiwei2::factory_implementation {
	struct MainPage : MainPageT<MainPage, implementation::MainPage> {};
}
