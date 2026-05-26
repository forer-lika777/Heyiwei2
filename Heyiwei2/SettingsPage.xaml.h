#pragma once

#include "SettingsPage.g.h"

namespace winrt::Heyiwei2::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
    private:
        bool darkModeIsOn = false;
        bool initialized = false;

    public:
        SettingsPage();

        void DarkModeIsOn(bool const& value);
        bool DarkModeIsOn();

        //void DarkModeToggle_Toggled(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
