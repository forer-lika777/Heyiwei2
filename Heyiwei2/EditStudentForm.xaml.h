#pragma once

#include "EditStudentForm.g.h"

namespace winrt::Heyiwei2::implementation
{
    struct EditStudentForm : EditStudentFormT<EditStudentForm>
    {
        EditStudentForm()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }

        int32_t MyProperty();
        void MyProperty(int32_t value);
    };
}

namespace winrt::Heyiwei2::factory_implementation
{
    struct EditStudentForm : EditStudentFormT<EditStudentForm, implementation::EditStudentForm>
    {
    };
}
