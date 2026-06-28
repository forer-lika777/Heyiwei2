#include "pch.h"
#include "DormListPage.xaml.h"
#if __has_include("DormListPage.g.cpp")
#include "DormListPage.g.cpp"
#include "winrt/Windows.UI.Popups.h"
#endif

#include <winrt/Windows.Foundation.h>
#include "App.xaml.h"

#include "IMainManager.h"

#include "Models.Dorm.h"
#include "Models.DormInfo.h"

#include "EditDormForm.xaml.h"
#include "DormManageForm.xaml.h"

#include "UiHelpers.h"

using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Microsoft::UI::Xaml::Controls;

namespace winrt::Heyiwei2::implementation {
	DormListPage::DormListPage() {

		InitializeComponent();
		mainManager = App::GetMainManager();
		dormItems = mainManager->getDormItems();
	}

	winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> DormListPage::DormItems() {
		return dormItems;
	}

	void DormListPage::openDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
		auto dataContext = button.DataContext();

		if (dataContext) {
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

	winrt::Windows::Foundation::IAsyncAction DormListPage::openCreateDormDialogAsync() {
		auto form = winrt::make_self<winrt::Heyiwei2::implementation::EditDormForm>();

		co_await UiHelpers::ShowStandardDialogAsync(this->XamlRoot(), L"添加宿舍", form.as<winrt::Heyiwei2::EditDormForm>(), [this, form](auto const&, auto const& args) {
			auto f = form.get();

			if (f->DormNumber() == L"") {
				f->showInfo(L"请输入宿舍号");
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
	}

	winrt::Windows::Foundation::IAsyncAction DormListPage::openDeleteDormDialogAsync(winrt::Heyiwei2::Models::Dorm const dorm) {
		co_await UiHelpers::ShowStandardDialogAsync(this->XamlRoot(), L"确定要删除此宿舍吗？", winrt::box_value(L"此操作不可逆"), [this, dorm](auto const&, auto const& args) {
			auto result = mainManager->removeDorm(dorm.DormId());

			if (!result.Success()) {
				args.Cancel(true);
				return;
			}
			});
	}

	void DormListPage::addDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		openCreateDormDialogAsync();
	}

	void DormListPage::DeleteDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
		auto dataContext = button.DataContext();

		if (dataContext) openDeleteDormDialogAsync(dataContext.as<Dorm>());
	}
}