#pragma once

#include "App.xaml.g.h"

using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Heyiwei2::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
		IObservableVector<IInspectable> dorms{ winrt::single_threaded_observable_vector<IInspectable>() };
		MainManager mainManager{ dorms };
    };
}
