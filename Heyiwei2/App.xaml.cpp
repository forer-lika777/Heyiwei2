#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"
#include "MainManager.h"
//#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Storage.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Heyiwei2::implementation {
	/// <summary>
	/// Initializes the singleton application object.  This is the first line of authored code
	/// executed, and as such is the logical equivalent of main() or WinMain().
	/// </summary>
	App::App() {
		// Xaml objects should not call InitializeComponent during construction.
		// See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
		UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e) {
			if (IsDebuggerPresent()) {
				auto errorMessage = e.Message();
				__debugbreak();
			}
			});
#endif
	}

	/// <summary>
	/// Invoked when the application is launched.
	/// </summary>
	/// <param name="e">Details about the launch request and process.</param>
	void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e) {
		dorms = winrt::single_threaded_observable_vector<IInspectable>();
		mainManager = new MainManager(dorms);
		mainManager->LoadStoredData();
		window = make<MainWindow>();

		auto settings = winrt::Windows::Storage::ApplicationData::Current().LocalSettings();
		auto themeValue = settings.Values().Lookup(L"AppTheme");

		if (themeValue) {
			auto themeInt = winrt::unbox_value<int32_t>(themeValue);
			auto theme = static_cast<winrt::Microsoft::UI::Xaml::ElementTheme>(themeInt);
			window.Content().as<winrt::Microsoft::UI::Xaml::FrameworkElement>().RequestedTheme(theme);
		}

		window.Activate();
	}

	Interfaces::IMainManager* App::GetMainManager() {
		return mainManager;
	}

	Interfaces::IMainManager* App::mainManager{ nullptr };
}
