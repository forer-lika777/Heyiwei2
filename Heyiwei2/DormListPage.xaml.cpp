#include "pch.h"
#include "DormListPage.xaml.h"
#if __has_include("DormListPage.g.cpp")
#include "DormListPage.g.cpp"
#include "winrt/Windows.UI.Popups.h"
#endif
//#include "DormManageForm.xaml.h"
#include "DormPaneItem.h"
#include "Models.Dorm.h"
#include "Models.DormInfo.h"
#include "Models.Result.h"
#include "Models.Student.h"
#include "Models.WaterRecord.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation::Collections;
using namespace winrt::Heyiwei2::Models::implementation;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Heyiwei2::implementation
{
    DormListPage::DormListPage()
    {
        InitializeComponent();
#ifdef _DEBUG
        auto dormInfo = winrt::make<DormInfo>();
        dormInfo.BuildingNumber(9);
        dormInfo.Floor(6);
        dormInfo.RoomNumber(28);

        auto dorm = winrt::make<Dorm>();
        dorm.Info(dormInfo);                        // 传入 DormInfo
        dorm.StartDateYear(2026);
        dorm.StartDateMonth(5);
        dorm.Index(0);

		dormItems.Append(winrt::make<DormPaneItem>(dorm.Info().ToString(), 0)); // 直接添加到 dormItems 中
#endif
    }

  //  void DormListPage::AddDormItem(Models::Dorm& dorm)
  //  {
		//dorms.Append(winrt::make<DormPaneItem>(dorm.info, dorms.Size()));
  //      RefreshDormListView({ dorm });
  //  }

  //  void DormListPage::AddDorms(std::vector<Models::Dorm>& dorms)
  //  {
  //      for (size_t i = 0; i < dorms.size(); ++i)
  //      {
		//	winrt::hstring dormInfo = dorms[i].info.toString();

		//	dormItems.Append(winrt::make<DormPaneItem>(dormInfo, i));
  //      }
  //      
		////dormListView().ItemsSource(dormItems);
  //  }
}

void winrt::Heyiwei2::implementation::DormListPage::openDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{

}

void winrt::Heyiwei2::implementation::DormListPage::addDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    auto dormInfo = winrt::make<DormInfo>();
    dormInfo.BuildingNumber(9);
    dormInfo.Floor(6);
    dormInfo.RoomNumber(28);

    auto dorm = winrt::make<Dorm>();
    dorm.Info(dormInfo);                        // 传入 DormInfo
    dorm.StartDateYear(2026);
    dorm.StartDateMonth(5);
    dorm.Index(0);

    dormItems.Append(winrt::make<DormPaneItem>(dorm.Info().ToString(), 0)); // 直接添加到 dormItems 中
}
