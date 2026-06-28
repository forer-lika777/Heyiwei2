#pragma once
#include <winrt/Microsoft.UI.Xaml.Controls.h>

class UiHelpers {
public:
    // 设为静态模板函数，并传入当前页面的 xamlRoot 
    template <typename TContent, typename TCallback>
    static winrt::Windows::Foundation::IAsyncAction ShowStandardDialogAsync(
        winrt::Microsoft::UI::Xaml::XamlRoot const& xamlRoot,
        winrt::hstring const& title,
        TContent const& content,
        TCallback onConfirm) {

        winrt::Microsoft::UI::Xaml::Controls::ContentDialog dialog;
        dialog.Title(winrt::box_value(title));
        dialog.Content(content);

        dialog.PrimaryButtonText(L"确认");
        dialog.CloseButtonText(L"取消");
        dialog.DefaultButton(winrt::Microsoft::UI::Xaml::Controls::ContentDialogButton::Primary);
        dialog.XamlRoot(xamlRoot);

        dialog.PrimaryButtonClick([onConfirm](auto const& sender, auto const& args) {
            onConfirm(sender, args);
            });

        co_await dialog.ShowAsync();
    }
};
