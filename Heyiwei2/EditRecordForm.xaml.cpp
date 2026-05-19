#include "pch.h"
#include "EditRecordForm.xaml.h"
#if __has_include("EditRecordForm.g.cpp")
#include "EditRecordForm.g.cpp"
#endif
#include "Utils.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Heyiwei2::implementation
{
    EditRecordForm::EditRecordForm() {
        //record = winrt::make<winrt::Heyiwei2::Models::implementation::WaterRecord>();
        years.ReplaceAll(Utils::generateYears(20));
        monthsThisYear = Utils::generateThisYearMonths();
        monthsPastYear = Utils::generatePastYearMonths();
        months.ReplaceAll(monthsThisYear);
        //record.Year(Utils::getCurrentYear());
        //record.Month(Utils::getCurrentMonth());
    }

    void EditRecordForm::refreshMonths(int32_t const& year) {

        if (year == Utils::getCurrentYear()) {
            months.ReplaceAll(monthsThisYear);
        }
        else {
            months.ReplaceAll(monthsPastYear);
        }
        MonthSelectComboBox().SelectedIndex(0);
    }

    void EditRecordForm::showInfo(hstring const& info) {
        OutputInfoTextBlock().Text(info);
    }

    winrt::Windows::Foundation::Collections::IObservableVector<int32_t> EditRecordForm::Years()
    {
        return years;
    }
    winrt::Windows::Foundation::Collections::IObservableVector<int32_t> EditRecordForm::Months()
    {
        return months;
    }
    int32_t EditRecordForm::Year()
    {
        return YearSelectComboBox().SelectedItem().as<int32_t>();
    }
    void EditRecordForm::Year(int32_t const& value) {
        for (size_t i = 0; i < years.Size(); ++i) {
            if (years.GetAt(i) == value) {
                YearSelectComboBox().SelectedIndex(i);
                refreshMonths(value);
                return;
            }
        }
    }
    int32_t EditRecordForm::Month()
    {
        return MonthSelectComboBox().SelectedItem().as<int32_t>();
    }
    void EditRecordForm::Month(int32_t const& value) {
        for (size_t i = 0; i < months.Size(); ++i) {
            if (months.GetAt(i) == value) {
                MonthSelectComboBox().SelectedIndex(i);
                return;
            }
        }
    }
    hstring EditRecordForm::Usage()
    {
        return UsageInput().Text();
    }
    void EditRecordForm::Usage(hstring const& value) {
        UsageInput().Text(value);
    }
    double EditRecordForm::Cost()
    {
        return cost;
    }
    void EditRecordForm::Cost(double const& value) {
        cost = value;
    }
    void EditRecordForm::CostDisplay(hstring const& value) {
        CostTextBlock().Text(value);
    }
    bool EditRecordForm::HasPaid()
    {
        return HasPaidCheckBox().IsChecked().GetBoolean();
    }
    void EditRecordForm::HasPaid(bool const& value) {
        HasPaidCheckBox().IsChecked(value);
    }
    void EditRecordForm::LockYearAndMonth() {
        YearSelectComboBox().IsEnabled(false);
        MonthSelectComboBox().IsEnabled(false);
    }
    void EditRecordForm::UsageInput_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e)
    {
        try {
            cost = Utils::calculateTotalWaterFee(std::stod(Usage().c_str()));
            CostDisplay(winrt::to_hstring(cost));
            //CostTextBlock().Text();
        }
        catch (...) {
            CostDisplay(L"-");
        }
    }
    void EditRecordForm::YearSelectComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e)
    {
        refreshMonths(Year());
    }
    //winrt::Windows::Foundation::IInspectable EditRecordForm::Record()
    //{
    //    Utils::calculateTotalWaterFee(record);
    //    return record;
    //}
    //void EditRecordForm::Record(winrt::Windows::Foundation::IInspectable const& value)
    //{
    //    record = value.as<winrt::Heyiwei2::Models::WaterRecord>();
    //}
}
