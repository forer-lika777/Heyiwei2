#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "DormListPage.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::Heyiwei2::implementation {
	MainPage::MainPage() {
		InitializeComponent();
	}

	void MainPage::openHomePage() {
		mainFrame().Navigate(xaml_typename<HomePage>());
	}

	void MainPage::openDormListPage() {
		auto page_impl = winrt::make_self<winrt::Heyiwei2::implementation::DormListPage>();
		mainFrame().Navigate(xaml_typename<winrt::Heyiwei2::DormListPage>(), *page_impl);  // 传参导航
	}

	void MainPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		openHomePage();
		navigationView().SelectedItem(navigationView().MenuItems().GetAt(0));
	}

	void MainPage::NavigationView_Invoked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args) {
		if (args.IsSettingsInvoked()) {

		}
		else {
			hstring tag = unbox_value<hstring>(args.InvokedItemContainer().Tag());
			if (currentPage == tag) return;
			currentPage = tag;
			if (tag == L"home") {
				openHomePage();
			}
			else if (tag == L"dormlist") {
				openDormListPage();
			}

		}
	}
}
