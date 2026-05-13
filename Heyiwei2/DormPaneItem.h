#pragma once
#include "DormPaneItem.g.h"

namespace winrt::Heyiwei2::implementation
{
    struct DormPaneItem : DormPaneItemT<DormPaneItem>
    {
        DormPaneItem() = default;

		DormPaneItem(hstring const& info, int32_t index) : dormInfo(info), index(index) {}

		hstring DormInfo() { return dormInfo; }
		void DormInfo(hstring const& value) { dormInfo = value; }

        int32_t Index() const { return index; }
		void Index(int32_t value) { index = value; }
    private:
        hstring dormInfo;
		int32_t index = 0;
    };
}
namespace winrt::Heyiwei2::factory_implementation
{
    struct DormPaneItem : DormPaneItemT<DormPaneItem, implementation::DormPaneItem>
    {
    };
}
