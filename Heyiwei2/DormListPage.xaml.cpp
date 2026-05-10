#include "pch.h"
#include "DormListPage.xaml.h"
#if __has_include("DormListPage.g.cpp")
#include "DormListPage.g.cpp"
#include "winrt/Windows.UI.Popups.h"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Heyiwei2::implementation
{
    DormListPage::DormListPage()
    {
        InitializeComponent();
        if (dormListView())
        {
            dormListView().Items().Append(winrt::box_value(L"628宿舍"));
        }
    }

    int32_t DormListPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void DormListPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }
}

void winrt::Heyiwei2::implementation::DormListPage::Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    // 1. 获取按钮对象 (转换类型)
    auto btn = sender.as<Microsoft::UI::Xaml::Controls::Button>();

    btn.Content(winrt::box_value(L"用水量:\n10000吨"));
}
