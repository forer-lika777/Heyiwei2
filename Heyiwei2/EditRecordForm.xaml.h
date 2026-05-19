#pragma once

#include "EditRecordForm.g.h"
#include "Models.WaterRecord.h"

namespace winrt::Heyiwei2::implementation
{
    struct EditRecordForm : EditRecordFormT<EditRecordForm>
    {
    private:
        void refreshMonths(int32_t const& year);

        winrt::Windows::Foundation::Collections::IObservableVector<int32_t> years{ winrt::single_threaded_observable_vector<int32_t>() };
        winrt::Windows::Foundation::Collections::IObservableVector<int32_t> months{ winrt::single_threaded_observable_vector<int32_t>() };

        std::vector<int32_t> monthsPastYear;
        std::vector<int32_t> monthsThisYear;

        //winrt::Heyiwei2::Models::WaterRecord record{ nullptr };

        //int32_t year;
        //int32_t month;
        //double usage;
        double cost;

    public:
        EditRecordForm();
        void showInfo(hstring const& info);

        winrt::Windows::Foundation::Collections::IObservableVector<int32_t> Years();
        winrt::Windows::Foundation::Collections::IObservableVector<int32_t> Months();

        int32_t Year();
        void Year(int32_t const& value);
        int32_t Month();
        void Month(int32_t const& value);
        hstring Usage();
        void Usage(hstring const& value);
        double Cost();
        void Cost(double const& value);
        void CostDisplay(hstring const& value);
        bool HasPaid();
        void HasPaid(bool const& value);

        void LockYearAndMonth();

        //winrt::Windows::Foundation::IInspectable Record();
        //void Record(winrt::Windows::Foundation::IInspectable const& value);
        void UsageInput_TextChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::TextChangedEventArgs const& e);
        void YearSelectComboBox_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::Controls::SelectionChangedEventArgs const& e);
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct EditRecordForm : EditRecordFormT<EditRecordForm, implementation::EditRecordForm>
    {
    };
}
