#include "pch.h"
#include "DormListPage.xaml.h"
#if __has_include("DormListPage.g.cpp")
#include "DormListPage.g.cpp"
#include "winrt/Windows.UI.Popups.h"
#endif
//#include "DormManageForm.xaml.h"
//#include "DormPaneItem.h"
#include "Models.Dorm.h"
#include "Models.DormInfo.h"
#include "Models.Result.h"
#include "Models.Student.h"
#include "Models.WaterRecord.h"
#include <winrt/Windows.Foundation.h>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;
using namespace Windows::Foundation::Collections;
using namespace winrt::Heyiwei2::Models;

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

		//dormItems.Append(winrt::make<DormPaneItem>(dorm.Info().ToString(), 0)); // 直接添加到 dormItems 中
#endif
    }
}

void winrt::Heyiwei2::implementation::DormListPage::openDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{

}

void winrt::Heyiwei2::implementation::DormListPage::addDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    AddUserDialog().XamlRoot(this->XamlRoot());
    auto showOperation = AddUserDialog().ShowAsync();

    showOperation.Completed([this](auto&& operation, auto&& /*status*/)
        {
            auto result = operation.GetResults();

            // 修改点 1: 确保 ContentDialogResult 的命名空间正确
            if (result == winrt::Microsoft::UI::Xaml::Controls::ContentDialogResult::Primary)
            {
                this->DispatcherQueue().TryEnqueue([this]()
                    {
                        try {
                            auto dormInfo = winrt::make<DormInfo>();
                            dormInfo.Region(RegionSelectComboBox().SelectedIndex());
                            dormInfo.BuildingNumber(BuildingSelectComboBox().SelectedIndex());
                            dormInfo.Floor(FloorSelectComboBox().SelectedIndex());
                            dormInfo.RoomNumber(std::stoi(DormNumberInput().Text().c_str()));

                            auto dorm = winrt::make<Dorm>();
                            dorm.Info(dormInfo);
                            dorm.StartDateYear(2026);
                            dorm.StartDateMonth(5);

                            dormItems.Append(dorm);
                        }
                        catch (...) {
                            OutputInfoTextBlock().Text(L"输入格式不正确，请重新输入。");
                        }
                        
                    }); // 这里是 TryEnqueue 的结束括号
            }
        }); // 这里是 Completed 的结束括号
}