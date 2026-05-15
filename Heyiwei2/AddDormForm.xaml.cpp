#include "pch.h"
#include "AddDormForm.xaml.h"
#if __has_include("AddDormForm.g.cpp")
#include "AddDormForm.g.cpp"
#endif

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Heyiwei2::implementation
{
    int32_t AddDormForm::Region()
    {
		return RegionSelectComboBox().SelectedIndex();
    }
    int32_t AddDormForm::BuildingNumber()
    {
		return BuildingSelectComboBox().SelectedIndex();
    }
    int32_t AddDormForm::FloorNumber()
    {
		return FloorSelectComboBox().SelectedIndex();
    }
    hstring AddDormForm::DormNumber()
    {
		return DormNumberInput().Text();
    }
    void AddDormForm::showInfo(hstring const& info) {
		OutputInfoTextBlock().Text(info);
    }
}
