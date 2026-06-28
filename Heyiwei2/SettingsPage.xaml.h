#pragma once

#include "SettingsPage.g.h"

namespace winrt::Heyiwei2::implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage>
    {
    private:
        int32_t darkModeStatus;
        //bool darkModeIsOn = false;
        bool initialized = false;

        void SaveThemeSetting(int32_t theme);
        int32_t LoadThemeSetting();

    public:
        SettingsPage();
        
        void DarkModeStatus(int32_t const& value);
        int32_t DarkModeStatus() const;

        //void DarkModeToggle_Toggled(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct SettingsPage : SettingsPageT<SettingsPage, implementation::SettingsPage>
    {
    };
}
