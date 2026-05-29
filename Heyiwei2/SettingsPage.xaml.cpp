#include "pch.h"
#include "SettingsPage.xaml.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif
//#include <winrt/Windows.Storage.h>
//#include "App.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::Heyiwei2::implementation
{
    SettingsPage::SettingsPage() {
        //auto settings = winrt::Windows::Storage::ApplicationData::Current().LocalSettings();
        //auto themeValue = settings.Values().Lookup(L"AppTheme");

        //if (themeValue) {
        //    auto themeInt = winrt::unbox_value<int32_t>(themeValue);
        //    darkModeIsOn = (themeInt == 2);  // 2 才是深色
        //}
    }

    void SettingsPage::DarkModeIsOn(bool const& value) {
        darkModeIsOn = value;

        auto theme = darkModeIsOn ? winrt::Microsoft::UI::Xaml::ElementTheme::Dark : winrt::Microsoft::UI::Xaml::ElementTheme::Light;

        // 应用到当前页面
        auto rootElement = this->XamlRoot().Content();
        if (rootElement) {
            rootElement.as<FrameworkElement>().RequestedTheme(theme);
        }

        // 保存设置
        //auto settings = winrt::Windows::Storage::ApplicationData::Current().LocalSettings();
        //settings.Values().Insert(
        //    L"AppTheme",
        //    winrt::box_value(static_cast<int32_t>(theme)));
    }

    bool SettingsPage::DarkModeIsOn() {
        return darkModeIsOn;
    }
}

