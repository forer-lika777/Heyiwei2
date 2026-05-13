#include "pch.h"
#include "DormListPage.xaml.h"
#if __has_include("DormListPage.g.cpp")
#include "DormListPage.g.cpp"
#include "winrt/Windows.UI.Popups.h"
#endif
#include "DormPaneItem.h"
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
                        // 修改点 2: 变量名统一。你前面拿的是 name，后面用的是 code，这里统一成 code
                        hstring name = UserNameInput().Text();
                        std::wstring code = name.c_str();

                        if (!name.empty() && code.length() >= 3) // 增加长度检查防止拆分崩溃
                        {
                            try {
                                // 拆分逻辑
                                int bld = code[0] - L'0';
                                int flr = code[1] - L'0';
                                int rm = std::stoi(code.substr(2));

                                std::wstring formattedName = std::to_wstring(bld) + L"栋" +
                                    std::to_wstring(flr) + L"-" +
                                    std::to_wstring(rm);

                                auto dormInfo = winrt::make<DormInfo>();
                                dormInfo.Region(0);
                                dormInfo.BuildingNumber(bld);
                                dormInfo.Floor(flr);
                                dormInfo.RoomNumber(rm);

                                auto dorm = winrt::make<Dorm>();
                                dorm.Info(dormInfo);
                                dorm.StartDateYear(2026);
                                dorm.StartDateMonth(5);

                                // 修改点 3: 你需要先“制做”要添加的项目对象 newItem
                                // 假设 DormPaneItem 接收一个字符串作为显示名称
                                auto newItem = winrt::make<DormPaneItem>(hstring(formattedName), 0);

                                // 修改点 4: 确保 dormItems 已经在头文件定义
                                dormItems.Append(newItem);

                                UserNameInput().Text(L"");
                            }
                            catch (...) {
                                // 处理 stoi 转换失败的情况
                            }
                        }
                    }); // 这里是 TryEnqueue 的结束括号
            }
        }); // 这里是 Completed 的结束括号
}