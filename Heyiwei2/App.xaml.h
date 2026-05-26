#pragma once

#include "App.xaml.g.h"
#include "MainManager.h"
#include "IMainManager.h"

using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Heyiwei2::implementation
{
    struct App : AppT<App>
    {
    public:
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);
        static Interfaces::IMainManager* GetMainManager();

    private:
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
		IObservableVector<IInspectable> dorms{ winrt::single_threaded_observable_vector<IInspectable>() };
	    static Interfaces::IMainManager* mainManager;
    };
}
