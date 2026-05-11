#pragma once

#include "DormListPage.g.h"
#include "Models.h"

namespace winrt::Heyiwei2::implementation
{
    struct DormListPage : DormListPageT<DormListPage>
    {
    private:
		std::vector <Models::Dorm> dorms; // 存储宿舍信息的成员变量

    public:
        DormListPage();
        
        int32_t MyProperty();
        void MyProperty(int32_t value);
		void AddDormItem(Models::Dorm& dorm);
		void RefreshDormListView();
        //void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void openDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct DormListPage : DormListPageT<DormListPage, implementation::DormListPage>
    {
    };
}
