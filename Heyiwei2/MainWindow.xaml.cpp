#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif
#include <MainPage.xaml.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::Heyiwei2::implementation {
	MainWindow::MainWindow() {
		ExtendsContentIntoTitleBar(true);

		mainPage = winrt::make<winrt::Heyiwei2::implementation::MainPage>();

		this->Content(mainPage);
	};
}