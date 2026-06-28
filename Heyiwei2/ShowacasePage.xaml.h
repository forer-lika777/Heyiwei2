#pragma once

#include "ShowacasePage.g.h"

namespace winrt::Heyiwei2::implementation {
    struct ShowacasePage : ShowacasePageT<ShowacasePage> {
        ShowacasePage() {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent
        }
    };
}

namespace winrt::Heyiwei2::factory_implementation {
    struct ShowacasePage : ShowacasePageT<ShowacasePage, implementation::ShowacasePage> {};
}