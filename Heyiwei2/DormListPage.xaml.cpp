#include "pch.h"
#include "DormListPage.xaml.h"
#if __has_include("DormListPage.g.cpp")
#include "DormListPage.g.cpp"
#include "winrt/Windows.UI.Popups.h"
#endif
#include "Models.Dorm.h"
#include "Models.DormInfo.h"
#include "Models.Result.h"
#include "Models.Student.h"
#include "Models.WaterRecord.h"
#include "IMainManager.h"
#include "EditDormForm.xaml.h"
#include "DormManageForm.xaml.h"
#include <winrt/Windows.Foundation.h>
#include "App.xaml.h"

using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;

namespace winrt::Heyiwei2::implementation
{
    DormListPage::DormListPage()
    {
        InitializeComponent();
        mainManager = App::GetMainManager();
        dormItems = mainManager->getDormItems();
    }
}

winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> winrt::Heyiwei2::implementation::DormListPage::DormItems()
{
    return dormItems;
}

void winrt::Heyiwei2::implementation::DormListPage::openDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
    auto dataContext = button.DataContext();

    if (dataContext)
    {
        auto form = winrt::make_self<winrt::Heyiwei2::implementation::DormManageForm>();
        form->Dorm(dataContext.as<winrt::Heyiwei2::Models::Dorm>());

        form->SetOnCloseCallback([this, form]() {
            DormManageView().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
            DormManageView().Children().RemoveAt(0);
            });

        DormManageView().Children().Append(*form);
        
        DormManageView().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
    }
}

void winrt::Heyiwei2::implementation::DormListPage::addDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{
    openCreateDormDialogAsync();
}

winrt::Windows::Foundation::IAsyncAction winrt::Heyiwei2::implementation::DormListPage::openCreateDormDialogAsync()
{
    auto form = winrt::make_self<winrt::Heyiwei2::implementation::EditDormForm>();

    ContentDialog dialog;
    dialog.Title(winrt::box_value(L"添加宿舍"));
    dialog.Content(form.as<winrt::Heyiwei2::EditDormForm>()); // 将 UserControl 设为内容

    dialog.PrimaryButtonText(L"确认");
    dialog.CloseButtonText(L"取消");
    dialog.DefaultButton(ContentDialogButton::Primary);

    dialog.XamlRoot(this->XamlRoot());
    dialog.PrimaryButtonClick([&](ContentDialog const&, ContentDialogButtonClickEventArgs const& args) {

        auto f = form.get();

        if (f->DormNumber() == L"") {
            f->showInfo(L"请输入宿舍号");
            args.Cancel(true);
            return;
        }

        if (mainManager == nullptr)
        {
            f->showInfo(L"发生程序内部错误：内部管理器指向了空指针");
            args.Cancel(true);
            return;
        }

        auto dormInfo = winrt::make<winrt::Heyiwei2::Models::implementation::DormInfo>();
        dormInfo.Region(form.get()->Region());
        dormInfo.BuildingNumber(form.get()->BuildingNumber());
        dormInfo.Floor(form.get()->FloorNumber());
        try {
            dormInfo.RoomNumber(std::stoi(form.get()->DormNumber().c_str()));
        }
        catch (const std::exception&) {
            f->showInfo(L"无法读取宿舍号：" + form.get()->DormNumber());
            args.Cancel(true);
            return;
        }

        dormInfo.StartDateYear(form.get()->StartYear());
        dormInfo.StartDateMonth(form.get()->StartMonth());

        auto dorm = winrt::make<winrt::Heyiwei2::Models::implementation::Dorm>();
        dorm.Info(dormInfo);

        auto result = mainManager->addDorm(dorm);

        if (!result.Success()) {
            f->showInfo(result.Message());
            args.Cancel(true);
            return;
        }
        });

    // 等待用户选择
    auto result = co_await dialog.ShowAsync();
}