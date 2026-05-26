#include "pch.h"
#include "DormManageForm.xaml.h"
#if __has_include("DormManageForm.g.cpp")
#include "DormManageForm.g.cpp"
#endif
#include "App.xaml.h"

#include "Models.DormInfo.h"
#include "Models.WaterRecord.h"

#include "DormListPage.xaml.h"

#include "EditDormForm.xaml.h"
#include "EditRecordForm.xaml.h"
#include "EditStudentForm.xaml.h"

using namespace winrt::Microsoft::UI::Xaml::Controls;
using winrt::Windows::Foundation::Collections::IObservableVector;
using winrt::Windows::Foundation::IInspectable;

namespace winrt::Heyiwei2::implementation {
	DormManageForm::DormManageForm() : mainManager(App::GetMainManager()) {

	}

	winrt::Heyiwei2::Models::Dorm DormManageForm::Dorm() {
		return dorm;
	}

	void DormManageForm::Dorm(winrt::Heyiwei2::Models::Dorm const& dorm) {
		this->dorm = dorm;
		this->DataContext(dorm);
		//DormManageForm: /*所有文本均绑定dorm*/
	}

	void DormManageForm::CloseButton_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		if (onCloseCallback) {
			onCloseCallback();
		}
	}

	void DormManageForm::SetOnCloseCallback(std::function<void()> callback) {
		onCloseCallback = callback;
	}

	void DormManageForm::EditDormButton_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		openEditDormDialogAsync();
	}

	winrt::Windows::Foundation::IAsyncAction DormManageForm::openEditDormDialogAsync() {
		auto form = winrt::make_self<winrt::Heyiwei2::implementation::EditDormForm>();

		auto f = form.get();

		auto info = dorm.Info();

		f->Region(info.Region());
		f->BuildingNumber(info.BuildingNumber());
		f->FloorNumber(info.Floor());
		f->DormNumber(winrt::to_hstring(info.RoomNumber()));
		f->StartYear(info.StartDateYear());
		f->StartMonth(info.StartDateMonth());

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

			if (mainManager == nullptr) {
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
			dormInfo.StartDateYear(form.get()->StartYear());
			dormInfo.StartDateMonth(form.get()->StartMonth());

			// 调用 addDorm 逻辑
			auto result = mainManager->updateDormInfo(this->dorm.DormId(), dormInfo);

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

	winrt::Windows::Foundation::IAsyncAction DormManageForm::openAddRecordDialogAsync() {
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
			record.HasPaid(f->HasPaid());

			auto result = mainManager->addWaterRecord(dorm.DormId(), record);

			if (!result.Success()) {
				args.Cancel(true);
				f->showInfo(result.Message());
				return;
			}
			});

		auto result = co_await dialog.ShowAsync();
	}

	winrt::Windows::Foundation::IAsyncAction DormManageForm::openEditRecordDialogAsync(winrt::Heyiwei2::Models::WaterRecord record) {
		auto form = winrt::make_self<winrt::Heyiwei2::implementation::EditRecordForm>();

		auto f = form.get();

		f->Year(record.Year());
		f->Month(record.Month());
		f->Usage(winrt::to_hstring(record.Usage()));
		f->HasPaid(record.HasPaid());
		f->LockYearAndMonth();

		ContentDialog dialog;
		dialog.Title(winrt::box_value(L"编辑用水记录"));
		dialog.Content(form.as<winrt::Heyiwei2::EditRecordForm>()); // 将 UserControl 设为内容
		dialog.PrimaryButtonText(L"确认");
		dialog.CloseButtonText(L"取消");
		dialog.DefaultButton(ContentDialogButton::Primary);
		dialog.XamlRoot(this->XamlRoot());

		dialog.PrimaryButtonClick([&](ContentDialog const&, ContentDialogButtonClickEventArgs const& args) {

			auto r = winrt::make<winrt::Heyiwei2::Models::implementation::WaterRecord>();

			r.Year(f->Year());
			r.Month(f->Month());

			try {
				r.Usage(std::stoi(form.get()->Usage().c_str()));
			}
			catch (const std::exception&) {
				f->showInfo(L"无法读取数据：" + form.get()->Usage());
				args.Cancel(true);
				return;
			}

			record.Cost(f->Cost());
			record.HasPaid(f->HasPaid());

			auto result = mainManager->updateWaterRecord(dorm.DormId(), record.Year(), record.Month(), r);

			if (!result.Success()) {
				args.Cancel(true);
				f->showInfo(result.Message());
				return;
			}
			});

		auto result = co_await dialog.ShowAsync();
	}

	winrt::Windows::Foundation::IAsyncAction DormManageForm::openDeleteRecordDialogAsync(winrt::Heyiwei2::Models::WaterRecord record) {
		ContentDialog dialog;
		dialog.Title(winrt::box_value(L"确定要删除此记录吗？"));
		dialog.Content(winrt::box_value(L"此操作不可逆"));
		dialog.PrimaryButtonText(L"确认");
		dialog.CloseButtonText(L"取消");
		dialog.DefaultButton(ContentDialogButton::Primary);
		dialog.XamlRoot(this->XamlRoot());

		dialog.PrimaryButtonClick([&](ContentDialog const&, ContentDialogButtonClickEventArgs const& args) {
			auto result = mainManager->removeWaterRecord(dorm.DormId(), record.Year(), record.Month());

			if (!result.Success()) {
				args.Cancel(true);
				dialog.Content(winrt::box_value(result.Message()));
				return;
			}
			});

		auto result = co_await dialog.ShowAsync();
	}

	winrt::Windows::Foundation::IAsyncAction DormManageForm::openBatchDeleteRecordDialogAsync() {
		ContentDialog dialog;
		dialog.Title(winrt::box_value(L"确定要删除这些记录吗？"));
		dialog.Content(winrt::box_value(L"此操作不可逆"));
		dialog.PrimaryButtonText(L"确认");
		dialog.CloseButtonText(L"取消");
		dialog.DefaultButton(ContentDialogButton::Primary);

		dialog.XamlRoot(this->XamlRoot());

		dialog.PrimaryButtonClick([&](ContentDialog const&, ContentDialogButtonClickEventArgs const& args) {

			std::vector<WaterRecord> records;
			for (auto r : RecordListView().SelectedItems()) {
				auto record = r.as<WaterRecord>();
				records.push_back(record);
			}

			for (auto& record : records) {
				auto result = mainManager->removeWaterRecord(dorm.DormId(), record.Year(), record.Month());
				if (!result.Success()) {
					args.Cancel(true);
					dialog.Content(winrt::box_value(result.Message()));
					return;
				}
			}
		});

		auto result = co_await dialog.ShowAsync();
	}

	winrt::Windows::Foundation::IAsyncAction DormManageForm::openAddStudentDialogAsync() {
		auto form = winrt::make_self<winrt::Heyiwei2::implementation::EditStudentForm>();

		auto f = form.get();

		ContentDialog dialog;
		dialog.Title(winrt::box_value(L"添加学生"));
		dialog.Content(form.as<winrt::Heyiwei2::EditStudentForm>()); // 将 UserControl 设为内容
		dialog.PrimaryButtonText(L"确认");
		dialog.CloseButtonText(L"取消");
		dialog.DefaultButton(ContentDialogButton::Primary);
		dialog.XamlRoot(this->XamlRoot());

		dialog.PrimaryButtonClick([&](ContentDialog const&, ContentDialogButtonClickEventArgs const& args) {

			auto student = winrt::make<winrt::Heyiwei2::Models::implementation::Student>();

			student.Name(f->Name());
			student.StudentId(f->StudentId());

			auto result = mainManager->addStudent(dorm.DormId(), student);

			if (!result.Success()) {
				args.Cancel(true);
				f->showInfo(result.Message());
				return;
			}
			});

		auto result = co_await dialog.ShowAsync();
	}

	winrt::Windows::Foundation::IAsyncAction DormManageForm::openEditStudentDialogAsync(winrt::Heyiwei2::Models::Student student) {
		auto form = winrt::make_self<winrt::Heyiwei2::implementation::EditStudentForm>();

		auto f = form.get();

		f->Name(student.Name());
		f->StudentId(student.StudentId());

		ContentDialog dialog;
		dialog.Title(winrt::box_value(L"编辑学生"));
		dialog.Content(form.as<winrt::Heyiwei2::EditStudentForm>()); // 将 UserControl 设为内容

		dialog.PrimaryButtonText(L"确认");
		dialog.CloseButtonText(L"取消");
		dialog.DefaultButton(ContentDialogButton::Primary);

		dialog.XamlRoot(this->XamlRoot());

		dialog.PrimaryButtonClick([&](ContentDialog const&, ContentDialogButtonClickEventArgs const& args) {

			auto s = winrt::make<winrt::Heyiwei2::Models::implementation::Student>();

			s.Name(f->Name());
			s.StudentId(f->StudentId());

			auto result = mainManager->updateStudent(dorm.DormId(), student.StudentId(), s);

			if (!result.Success()) {
				args.Cancel(true);
				f->showInfo(result.Message());
				return;
			}
			});

		auto result = co_await dialog.ShowAsync();
	}

	winrt::Windows::Foundation::IAsyncAction DormManageForm::openDeleteStudentDialogAsync(winrt::Heyiwei2::Models::Student student) {
		ContentDialog dialog;
		dialog.Title(winrt::box_value(L"确定要删除此学生吗？"));
		dialog.Content(winrt::box_value(L"此操作不可逆"));
		dialog.PrimaryButtonText(L"确认");
		dialog.CloseButtonText(L"取消");
		dialog.DefaultButton(ContentDialogButton::Primary);

		dialog.XamlRoot(this->XamlRoot());

		dialog.PrimaryButtonClick([&](ContentDialog const&, ContentDialogButtonClickEventArgs const& args) {
			auto result = mainManager->removeStudent(dorm.DormId(), student.StudentId());

			if (!result.Success()) {
				args.Cancel(true);
				dialog.Content(winrt::box_value(result.Message()));
				return;
			}
			});

		auto result = co_await dialog.ShowAsync();
	}

	winrt::Windows::Foundation::IAsyncAction DormManageForm::openBatchDeleteStudentDialogAsync() {
		ContentDialog dialog;
		dialog.Title(winrt::box_value(L"确定要删除这些学生吗？"));
		dialog.Content(winrt::box_value(L"此操作不可逆"));
		dialog.PrimaryButtonText(L"确认");
		dialog.CloseButtonText(L"取消");
		dialog.DefaultButton(ContentDialogButton::Primary);

		dialog.XamlRoot(this->XamlRoot());

		dialog.PrimaryButtonClick([&](ContentDialog const&, ContentDialogButtonClickEventArgs const& args) {

			// 先收集选择的学生学号，因为遍历的同时删除元素会引发异常
			std::vector<hstring> selectedIds;
			for (auto s : StudentListView().SelectedItems()) {
				auto student = s.as<Student>();
				selectedIds.push_back(student.StudentId());
			}

			for (auto& id : selectedIds) {
				auto result = mainManager->removeStudent(dorm.DormId(), id);
				if (!result.Success()) {
					args.Cancel(true);
					dialog.Content(winrt::box_value(result.Message()));
					return;
				}
			}
		});

		auto result = co_await dialog.ShowAsync();
	}

	void DormManageForm::AddRecordButton_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		openAddRecordDialogAsync();
	}

	void DormManageForm::DeleteRecordButton_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
		auto dataContext = button.DataContext();

		if (dataContext) openDeleteRecordDialogAsync(dataContext.as<WaterRecord>());
	}

	void DormManageForm::EditRecordButton_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
		auto dataContext = button.DataContext();

		if (dataContext) openEditRecordDialogAsync(dataContext.as<WaterRecord>());
	}

	void DormManageForm::AddStudentButton_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		openAddStudentDialogAsync();
	}

	void DormManageForm::EditStudentButton_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
		auto dataContext = button.DataContext();

		if (dataContext) openEditStudentDialogAsync(dataContext.as<Student>());
	}

	void DormManageForm::DeleteStudentButton_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		auto button = sender.as<winrt::Microsoft::UI::Xaml::Controls::Button>();
		auto dataContext = button.DataContext();

		if (dataContext) openDeleteStudentDialogAsync(dataContext.as<Student>());
	}

	void DormManageForm::StudentListView_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e) {
		if (StudentListView().SelectedItems().Size() > 1) {
			StudentBatchDeleteButton().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		}
		else {
			StudentBatchDeleteButton().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
		}
	}

	void DormManageForm::RecordListView_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e) {
		if (RecordListView().SelectedItems().Size() > 1) {
			RecordBatchDeleteButton().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Visible);
		}
		else {
			RecordBatchDeleteButton().Visibility(winrt::Microsoft::UI::Xaml::Visibility::Collapsed);
		}
	}

	void DormManageForm::StudentBatchDeleteButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		openBatchDeleteStudentDialogAsync();
	}

	void DormManageForm::RecordBatchDeleteButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e) {
		openBatchDeleteRecordDialogAsync();
	}

	
}
