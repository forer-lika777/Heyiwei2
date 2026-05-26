#pragma once

#include "DormListPage.g.h"
#include <winrt/Windows.Foundation.Collections.h>
#include "IMainManager.h"

namespace winrt::Heyiwei2::implementation
{
    struct DormListPage : DormListPageT<DormListPage>
    {
    private:
        winrt::Windows::Foundation::IAsyncAction openCreateDormDialogAsync();
        winrt::Windows::Foundation::IAsyncAction openDeleteDormDialogAsync(winrt::Heyiwei2::Models::Dorm const dorm);

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> dormItems{ nullptr }; // 存储宿舍信息的成员变量
		Interfaces::IMainManager* mainManager = nullptr; // 指向 MainManager 的指针

    public:
        DormListPage();

        winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> DormItems();

        void openDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void addDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void DeleteDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct DormListPage : DormListPageT<DormListPage, implementation::DormListPage>
    {
    };
}
