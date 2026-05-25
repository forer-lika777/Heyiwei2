#pragma once

#include "DormManageForm.g.h"
#include "Models.Dorm.h"
#include "DormListPage.xaml.h"
#include "IMainManager.h"
#include <functional>

namespace winrt::Heyiwei2::implementation
{
    struct DormManageForm : DormManageFormT<DormManageForm>
    {
    private:
        winrt::Heyiwei2::Models::Dorm dorm;
        Interfaces::IMainManager* mainManager = nullptr;

        std::function<void()> onCloseCallback;

        winrt::Windows::Foundation::IAsyncAction openEditDormDialogAsync();

        winrt::Windows::Foundation::IAsyncAction openAddRecordDialogAsync();
        winrt::Windows::Foundation::IAsyncAction openEditRecordDialogAsync(winrt::Heyiwei2::Models::WaterRecord record);
        winrt::Windows::Foundation::IAsyncAction openDeleteRecordDialogAsync(winrt::Heyiwei2::Models::WaterRecord record);

        winrt::Windows::Foundation::IAsyncAction openAddStudentDialogAsync();
        winrt::Windows::Foundation::IAsyncAction openEditStudentDialogAsync(winrt::Heyiwei2::Models::Student student);
        winrt::Windows::Foundation::IAsyncAction openDeleteStudentDialogAsync(winrt::Heyiwei2::Models::Student student);
        winrt::Windows::Foundation::IAsyncAction openBatchDeleteStudentDialogAsync();

    public:
        DormManageForm();

        winrt::Heyiwei2::Models::Dorm Dorm();
        void Dorm(winrt::Heyiwei2::Models::Dorm const& dorm);

        void CloseButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void SetOnCloseCallback(std::function<void()> callback);

        void EditDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void AddRecordButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void EditRecordButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void DeleteRecordButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void AddStudentButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void EditStudentButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void DeleteStudentButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void StudentBatchDeleteButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);

        void StudentListView_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct DormManageForm : DormManageFormT<DormManageForm, implementation::DormManageForm>
    {
    };
}
