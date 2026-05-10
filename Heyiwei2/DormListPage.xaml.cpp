#include "pch.h"
#include "DormListPage.xaml.h"
#if __has_include("DormListPage.g.cpp")
#include "DormListPage.g.cpp"
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
            dormListView().Items().Append(winrt::box_value(L"628"));
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
