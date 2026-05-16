#pragma once

#include "EditDormForm.g.h"

namespace winrt::Heyiwei2::implementation
{
    struct EditDormForm : EditDormFormT<EditDormForm>
    {
    private:
        winrt::Windows::Foundation::Collections::IObservableVector<int32_t> years{ winrt::single_threaded_observable_vector<int32_t>() };
        winrt::Windows::Foundation::Collections::IObservableVector<int32_t> months{ winrt::single_threaded_observable_vector<int32_t>() };

    public:
        EditDormForm();

        int32_t Region();
        void Region(int32_t const& value);

        int32_t BuildingNumber();
        void BuildingNumber(int32_t const& value);

        int32_t FloorNumber();
        void FloorNumber(int32_t const& value);

        hstring DormNumber();
        void DormNumber(hstring const& value);

        int32_t StartYear();
        void StartYear(int32_t const& value);

        int32_t StartMonth();
        void StartMonth(int32_t const& value);

        winrt::Windows::Foundation::Collections::IObservableVector<int32_t> Years();
        winrt::Windows::Foundation::Collections::IObservableVector<int32_t> Months();
        
		void showInfo(hstring const& info);
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct EditDormForm : EditDormFormT<EditDormForm, implementation::EditDormForm>
    {
    };
}
