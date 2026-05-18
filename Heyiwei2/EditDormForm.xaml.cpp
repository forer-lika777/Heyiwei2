#include "pch.h"
#include "EditDormForm.xaml.h"
#if __has_include("EditDormForm.g.cpp")
#include "EditDormForm.g.cpp"
#endif
#include "Utils.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Heyiwei2::implementation
{
    void EditDormForm::refreshMonths(int32_t const& year) {
        if (year == Utils::getCurrentYear()) {
            months.ReplaceAll(monthsThisYear);
        }
        else {
            months.ReplaceAll(monthsPastYear);
        }
        StartMonthSelectComboBox().SelectedIndex(0);
    }
    EditDormForm::EditDormForm() {
        years.ReplaceAll(Utils::generateYears(20));
        monthsThisYear = Utils::generateThisYearMonths();
        monthsPastYear = Utils::generatePastYearMonths();

        months.ReplaceAll(monthsThisYear);
        //StartYearSelectComboBox().DataContext(months);
    }

    int32_t EditDormForm::Region()
    {
		return RegionSelectComboBox().SelectedIndex();
    }
    void EditDormForm::Region(int32_t const& value) {
        RegionSelectComboBox().SelectedIndex(value);
    }
    int32_t EditDormForm::BuildingNumber()
    {
        return BuildingSelectComboBox().SelectedIndex() + 1;
    }
    void EditDormForm::BuildingNumber(int32_t const& value) {
        BuildingSelectComboBox().SelectedIndex(value - 1);
    }
    int32_t EditDormForm::FloorNumber()
    {
		return FloorSelectComboBox().SelectedIndex() + 1;
    }
    void EditDormForm::FloorNumber(int32_t const& value) {
        FloorSelectComboBox().SelectedIndex(value - 1);
    }
    hstring EditDormForm::DormNumber()
    {
		return DormNumberInput().Text();
    }
    void EditDormForm::DormNumber(hstring const& value) {
        DormNumberInput().Text(value);
    }
    int32_t EditDormForm::StartYear()
    {
        return StartYearSelectComboBox().SelectedItem().as<int32_t>();
    }
    void EditDormForm::StartYear(int32_t const& value) {
        for (size_t i = 0; i < years.Size(); ++i) {
            if (years.GetAt(i) == value) {
                StartYearSelectComboBox().SelectedIndex(i);
                refreshMonths(value);
                return;
            }
        }
    }
    int32_t EditDormForm::StartMonth()
    {
        return StartMonthSelectComboBox().SelectedItem().as<int32_t>();
    }
    void EditDormForm::StartMonth(int32_t const& value) {
        for (size_t i = 0; i < months.Size(); ++i) {
            if (months.GetAt(i) == value) {
                StartMonthSelectComboBox().SelectedIndex(i);
                return;
            }
        }
    }
    winrt::Windows::Foundation::Collections::IObservableVector<int32_t> EditDormForm::Years()
    {
        return years;
    }
    winrt::Windows::Foundation::Collections::IObservableVector<int32_t> EditDormForm::Months()
    {
        return months;
    }
    void EditDormForm::showInfo(hstring const& info) {
		OutputInfoTextBlock().Text(info);
    }
    void EditDormForm::StartYearSelectComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
    {
        refreshMonths(StartYear());
    }
}
