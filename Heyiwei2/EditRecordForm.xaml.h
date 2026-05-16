#pragma once

#include "EditRecordForm.g.h"

namespace winrt::Heyiwei2::implementation
{
    struct EditRecordForm : EditRecordFormT<EditRecordForm>
    {
    private:
        winrt::Windows::Foundation::Collections::IObservableVector<int32_t> years{ nullptr };
        winrt::Windows::Foundation::Collections::IObservableVector<int32_t> months{ nullptr };

    public:
        EditRecordForm()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        winrt::Windows::Foundation::Collections::IObservableVector<int32_t> Years();
        winrt::Windows::Foundation::Collections::IObservableVector<int32_t> Months();
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct EditRecordForm : EditRecordFormT<EditRecordForm, implementation::EditRecordForm>
    {
    };
}
