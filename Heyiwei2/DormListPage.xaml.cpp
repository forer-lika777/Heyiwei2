#include "pch.h"
#include "DormListPage.xaml.h"
#if __has_include("DormListPage.g.cpp")
#include "DormListPage.g.cpp"
#include "winrt/Windows.UI.Popups.h"
#endif
#include "Models.h"
#include "DormManageForm.xaml.h"
#include "DormPaneItem.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation::Collections;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Heyiwei2::implementation
{
    DormListPage::DormListPage()
    {
        InitializeComponent();
#ifdef _DEBUG
        Models::Dorm dorm;
        Models::DormInfo info{};
        info.region = Models::Region::East;
        info.buildingNumber = 9;
        info.floor = 6;
        info.roomNumber = 28;
        dorm.info = info;
        std::vector<Models::Dorm> dorms = { dorm, dorm };
        AddDorms(dorms);
#endif
    }

  //  void DormListPage::AddDormItem(Models::Dorm& dorm)
  //  {
		//dorms.Append(winrt::make<DormPaneItem>(dorm.info, dorms.Size()));
  //      RefreshDormListView({ dorm });
  //  }

    void DormListPage::AddDorms(std::vector<Models::Dorm>& dorms)
    {
        for (size_t i = 0; i < dorms.size(); ++i)
        {
			winrt::hstring dormInfo = dorms[i].info.toString();

			dormItems.Append(winrt::make<DormPaneItem>(dormInfo, i));
        }
        
		//dormListView().ItemsSource(dormItems);
    }
}

void winrt::Heyiwei2::implementation::DormListPage::openDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{

}

void winrt::Heyiwei2::implementation::DormListPage::addDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    Models::Dorm dorm;
    Models::DormInfo info{};
    info.region = Models::Region::East;
    info.buildingNumber = 9;
    info.floor = 6;
    info.roomNumber = 28;
    dorm.info = info;
    std::vector<Models::Dorm> dorms = { dorm };
    AddDorms(dorms);
}
