#pragma once

#include "App.xaml.g.h"
#include "MainManager.h"
#include "IMainManager.h"

using namespace winrt::Windows::Foundation::Collections;

// 全局变量和函数，放在命名空间外面
//static Interfaces::IMainManager* g_mainManager = nullptr;
//
//Interfaces::IMainManager* GetMainManager()
//{
//    return g_mainManager;
//}

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
