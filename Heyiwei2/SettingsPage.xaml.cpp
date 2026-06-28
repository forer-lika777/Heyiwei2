#include "pch.h"
#include "SettingsPage.xaml.h"
#if __has_include("SettingsPage.g.cpp")
#include "SettingsPage.g.cpp"
#endif
#include <fstream>
#include <cereal/archives/json.hpp>
//#include <winrt/Windows.Storage.h>
//#include "App.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::Heyiwei2::implementation
{
    SettingsPage::SettingsPage() {
        darkModeStatus = LoadThemeSetting();
        //auto settings = winrt::Windows::Storage::ApplicationData::Current().LocalSettings();
        //auto themeValue = settings.Values().Lookup(L"AppTheme");

        //if (themeValue) {
        //    auto themeInt = winrt::unbox_value<int32_t>(themeValue);
        //    darkModeIsOn = (themeInt == 2);  // 2 才是深色
        //}
    }

    struct ThemeConfig {
        int32_t theme = 0; // 0=Default, 1=Light, 2=Dark
        template<class Archive>
        void serialize(Archive& archive) {
            archive(CEREAL_NVP(theme));
        }
    };

    // 保存主题设置到本地 JSON 文件
    void SettingsPage::SaveThemeSetting(int32_t theme) {
        ThemeConfig config{ theme };
        std::ofstream file("theme_config.json");
        cereal::JSONOutputArchive archive(file);
        archive(CEREAL_NVP(config));
    }

    // 从本地 JSON 文件读取主题设置
    int32_t SettingsPage::LoadThemeSetting() {
        std::ifstream file("theme_config.json");
        if (file.is_open()) {
            ThemeConfig config;
            cereal::JSONInputArchive archive(file);
            archive(CEREAL_NVP(config));
            return config.theme;
        }
        return 0; // 默认返回 Default
    }

    void SettingsPage::DarkModeStatus(int32_t const& value) {
        darkModeStatus = value;
        auto theme = winrt::Microsoft::UI::Xaml::ElementTheme::Default;

        if (darkModeStatus == 0) {
            theme = winrt::Microsoft::UI::Xaml::ElementTheme::Default;
        }
        else if (darkModeStatus == 1) {
            theme = winrt::Microsoft::UI::Xaml::ElementTheme::Light;
        }
        else if (darkModeStatus == 2) {
            theme = winrt::Microsoft::UI::Xaml::ElementTheme::Dark;
        }
        // 应用到当前页面
        auto rootElement = this->XamlRoot().Content();
        if (rootElement) {
            rootElement.as<FrameworkElement>().RequestedTheme(theme);
        }

        SaveThemeSetting(value);
    }

    int32_t SettingsPage::DarkModeStatus() const {
        return darkModeStatus;
    }
}

