#include "pch.h"
#include "DormManageForm.xaml.h"
#if __has_include("DormManageForm.g.cpp")
#include "DormManageForm.g.cpp"
#endif
#include "DormListPage.xaml.h"
#include "App.xaml.h"
#include "EditDormForm.xaml.h"
#include "Models.DormInfo.h"
#include "EditRecordForm.xaml.h"
#include "Models.WaterRecord.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml::Controls;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Heyiwei2::implementation
{
    
    DormManageForm::DormManageForm() {
        mainManager = App::GetMainManager();
    }

    winrt::Heyiwei2::Models::Dorm DormManageForm::Dorm() {
        return dorm;
    }

    void DormManageForm::Dorm(winrt::Heyiwei2::Models::Dorm const& dorm) {
        this->dorm = dorm;
        this->DataContext(dorm); 
    //DormManageForm: /*所有文本均绑定dorm*/
    }

    void DormManageForm::CloseButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        if (onCloseCallback) {
            onCloseCallback();
        }
    }
    void DormManageForm::SetOnCloseCallback(std::function<void()> callback) {
        onCloseCallback = callback;
    }
    void DormManageForm::EditDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
        openEditDormDialogAsync();
    }

    winrt::Windows::Foundation::IAsyncAction DormManageForm::openEditDormDialogAsync()
    {
        auto form = winrt::make_self<winrt::Heyiwei2::implementation::EditDormForm>();

        auto f = form.get();

        auto info = dorm.Info();

        f->Region(info.Region());
        f->BuildingNumber(info.BuildingNumber());
        f->FloorNumber(info.Floor());
        f->DormNumber(winrt::to_hstring(info.RoomNumber()));
        f->StartYear(dorm.StartDateYear());
        f->StartMonth(dorm.StartDateMonth());

        ContentDialog dialog;
        dialog.Title(winrt::box_value(L"编辑宿舍"));
        dialog.Content(form.as<winrt::Heyiwei2::EditDormForm>()); // 将 UserControl 设为内容

        dialog.PrimaryButtonText(L"确认");
        dialog.CloseButtonText(L"取消");
        dialog.DefaultButton(ContentDialogButton::Primary);

        dialog.XamlRoot(this->XamlRoot());

        dialog.PrimaryButtonClick([&](ContentDialog const&, ContentDialogButtonClickEventArgs const& args) {

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
                f->showInfo(L"无法读取数据：" + form.get()->DormNumber());
                args.Cancel(true);
                return;
            }

            auto dorm = winrt::make<winrt::Heyiwei2::Models::implementation::Dorm>();
            dorm.Info(dormInfo);
            dorm.StartDateYear(form.get()->StartYear());
            dorm.StartDateMonth(form.get()->StartMonth());

            // 调用 addDorm 逻辑
            auto result = mainManager->updateDorm(this->dorm.DormId(), dorm);

            if (!result.Success()) {
                args.Cancel(true);
                f->showInfo(result.Message());
                return;
            }
            this->Dorm();
        });

        // 等待用户选择
        auto result = co_await dialog.ShowAsync();
    }
    winrt::Windows::Foundation::IAsyncAction DormManageForm::openAddRecordDialogAsync()
    {
        auto form = winrt::make_self<winrt::Heyiwei2::implementation::EditRecordForm>();

        auto f = form.get();

        ContentDialog dialog;
        dialog.Title(winrt::box_value(L"添加用水记录"));
        dialog.Content(form.as<winrt::Heyiwei2::EditRecordForm>()); // 将 UserControl 设为内容

        dialog.PrimaryButtonText(L"确认");
        dialog.CloseButtonText(L"取消");
        dialog.DefaultButton(ContentDialogButton::Primary);

        dialog.XamlRoot(this->XamlRoot());

        dialog.PrimaryButtonClick([&](ContentDialog const&, ContentDialogButtonClickEventArgs const& args) {

            auto record = winrt::make<winrt::Heyiwei2::Models::implementation::WaterRecord>();

            record.Year(f->Year());
            record.Month(f->Month());

            try {
                record.Usage(std::stoi(form.get()->Usage().c_str()));
            }
            catch (const std::exception&) {
                f->showInfo(L"无法读取数据：" + form.get()->Usage());
                args.Cancel(true);
                return;
            }
            //record.Usage(f->Usage());
            record.Cost(f->Cost());

            auto result = mainManager->addWaterRecord(dorm.DormId(), record);

            if (!result.Success()) {
                args.Cancel(true);
                f->showInfo(result.Message());
                return;
            }
        });

        auto result = co_await dialog.ShowAsync();
    }
    void DormManageForm::AddRecordButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
    {
        openAddRecordDialogAsync();
    }
}
