#pragma once
#include "DormPaneItem.g.h"

namespace winrt::Heyiwei2::implementation
{
    struct DormPaneItem : DormPaneItemT<DormPaneItem>
    {
        DormPaneItem() = default;

        DormPaneItem(hstring const& name, int32_t index);
        hstring DormInfo();
        void DormInfo(hstring const& value);
        int32_t Index();
        void Index(int32_t value);
    };
}
namespace winrt::Heyiwei2::factory_implementation
{
    struct DormPaneItem : DormPaneItemT<DormPaneItem, implementation::DormPaneItem>
    {
    };
}
