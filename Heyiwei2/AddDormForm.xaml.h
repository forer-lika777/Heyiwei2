#pragma once

#include "AddDormForm.g.h"

namespace winrt::Heyiwei2::implementation
{
    struct AddDormForm : AddDormFormT<AddDormForm>
    {
        AddDormForm()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t Region();
        int32_t BuildingNumber();
        int32_t FloorNumber();
        hstring DormNumber();
		void showInfo(hstring const& info);
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct AddDormForm : AddDormFormT<AddDormForm, implementation::AddDormForm>
    {
    };
}
