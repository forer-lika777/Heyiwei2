#pragma once
#include "Models.DormInfo.g.h"
#include <winrt/Windows.UI.Xaml.Data.h>

namespace winrt::Heyiwei2::Models::implementation
{
    struct DormInfo : DormInfoT<DormInfo>
    {
    public:
        DormInfo() = default;

        int32_t Region() const;
        void Region(int32_t value);
        int32_t BuildingNumber() const;
        void BuildingNumber(int32_t value);
        int32_t Floor() const;
        void Floor(int32_t value);
        int32_t RoomNumber() const;
        void RoomNumber(int32_t value);
        hstring ToString();
    private:
        int32_t region = 0;
        int32_t buildingNumber = 0;
        int32_t floor = 0;
        int32_t roomNumber = 0;
    };
}
