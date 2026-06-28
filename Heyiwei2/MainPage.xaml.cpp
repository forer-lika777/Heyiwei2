#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif
#include "winrt/Windows.UI.Xaml.Interop.h"
#include "DormListPage.xaml.h"
#include "MainWindow.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::Heyiwei2::implementation {
	MainPage::MainPage() {
		InitializeComponent();
	}

	void MainPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		openHomePage();
		navigationView().SelectedItem(navigationView().MenuItems().GetAt(0));
	}

	void MainPage::NavigationView_Invoked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args) {
		if (args.IsSettingsInvoked()) {
			currentPage = L"settings";
			openSettingsPage();
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
			else if (tag == L"showacase") {
				openShowacasePage();
			}
		}
	}

	void MainPage::openHomePage() {
		mainFrame().Navigate(xaml_typename<HomePage>());
	}

	void MainPage::openDormListPage() {
		mainFrame().Navigate(xaml_typename<winrt::Heyiwei2::DormListPage>());  // 传参导航
	}

	void MainPage::openSettingsPage() {
		mainFrame().Navigate(xaml_typename<SettingsPage>());
	}

	void MainPage::openShowacasePage() {
		mainFrame().Navigate(xaml_typename<winrt::Heyiwei2::ShowacasePage>());
	}
}
