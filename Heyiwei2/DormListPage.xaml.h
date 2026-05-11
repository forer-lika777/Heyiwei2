#pragma once

#include "DormListPage.g.h"
#include "Models.h"
#include <winrt/Windows.Foundation.Collections.h>
#include "DormPaneItem.h"

using namespace winrt::Windows::Foundation;

namespace winrt::Heyiwei2::implementation
{
    struct DormListPage : DormListPageT<DormListPage>
    {
    private:
        Collections::IObservableVector<IInspectable> dorms{ winrt::single_threaded_observable_vector<IInspectable>() }; // 存储宿舍信息的成员变量

    public:
        DormListPage();
        
        Collections::IObservableVector<IInspectable> DormItems() { return dorms; }
        int32_t MyProperty();
        void MyProperty(int32_t value);
		void AddDormItem(Models::Dorm& dorm);
		void RefreshDormListView();
        //void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
        void openDormButton_Click(IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct DormListPage : DormListPageT<DormListPage, implementation::DormListPage>
    {
    };
}
