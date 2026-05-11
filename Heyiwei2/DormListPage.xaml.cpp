#include "pch.h"
#include "DormListPage.xaml.h"
#if __has_include("DormListPage.g.cpp")
#include "DormListPage.g.cpp"
#include "winrt/Windows.UI.Popups.h"
#endif
#include "Models.h"
#include "DormManageForm.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation::Collections;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Heyiwei2::implementation
{
    DormListPage::DormListPage()
    {
        InitializeComponent();
#ifdef _DEBUG
        Models::Dorm dorm;
        Models::DormInfo info{};
        info.region = Models::Region::East;
        info.buildingNumber = 9;
        info.floor = 6;
        info.roomNumber = 28;
        dorm.info = info;
        std::vector<Models::Dorm> dorms = { dorm };
        AddDormItem(dorm);
#endif
    }

    int32_t DormListPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void DormListPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void DormListPage::AddDormItem(Models::Dorm& dorm)
    {
		dorms.push_back(dorm);
        RefreshDormListView();
    }

    void DormListPage::RefreshDormListView()
    {
		auto items = winrt::single_threaded_observable_vector<IInspectable>();

        for (size_t i = 0; i < dorms.size(); ++i)
        {
			winrt::hstring dormInfo = dorms[i].info.toString();

            auto create_item = [](int32_t index, hstring text) {
                PropertySet item;
                item.Insert(L"info", box_value(text));
                return item; };

			items.Append(create_item(static_cast<int32_t>(i), dormInfo));
        }

		dormListView().ItemsSource(items);
    }
}

void winrt::Heyiwei2::implementation::DormListPage::openDormButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& e)
{

}
