#include "pch.h"
#include "MainPage.xaml.h"
#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif
#include "winrt/Windows.UI.Xaml.Interop.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Heyiwei2::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    MainPage::MainPage(MainManager* manager)
        : mainManager(manager)
    {
        InitializeComponent();
        // 这里用 mainManager 绑定数据
    }

    void MainPage::openHomePage() {
        mainFrame().Navigate(xaml_typename<HomePage>());
    }

    void MainPage::openDormListPage() {
        mainFrame().Navigate(xaml_typename<DormListPage>());
    }

    void MainPage::Page_Loaded(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        openHomePage();
		navigationView().SelectedItem(navigationView().MenuItems().GetAt(0));
    }

    void MainPage::NavigationView_Invoked(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::NavigationViewItemInvokedEventArgs const& args) {
        if (args.IsSettingsInvoked()) {

        }
        else {
            hstring tag = unbox_value<hstring>(args.InvokedItemContainer().Tag());
            if (tag == L"home") {
                openHomePage();
            }
            else if (tag == L"dormlist") {
                openDormListPage();
            }

        }
    }
}
