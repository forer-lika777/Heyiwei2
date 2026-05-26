#pragma once

#include "MainWindow.g.h"

namespace winrt::Heyiwei2::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
    public:
        MainWindow();
        //static MainWindow GetMainManager();

    private:
        winrt::Heyiwei2::MainPage mainPage{ nullptr };
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
