#pragma once

#include "DormListPage.g.h"

namespace winrt::Heyiwei2::implementation
{
    struct DormListPage : DormListPageT<DormListPage>
    {
        DormListPage()
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
    struct DormListPage : DormListPageT<DormListPage, implementation::DormListPage>
    {
    };
}
