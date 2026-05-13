#pragma once

#include "MainWindow.g.h"
#include "MainManager.h"

namespace winrt::Heyiwei2::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
    public:
        MainWindow(MainManager& manager);
    private:
		MainManager& mainManager;
        winrt::Heyiwei2::MainPage mainPage{ nullptr };
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
