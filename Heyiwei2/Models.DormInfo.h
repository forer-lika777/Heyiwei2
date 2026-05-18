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

        int32_t StartDateYear();
        void StartDateYear(int32_t value);
        int32_t StartDateMonth();
        void StartDateMonth(int32_t value);

        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler) {
            return propertyChanged.add(handler);
        }

        void PropertyChanged(winrt::event_token const& token) noexcept {
            propertyChanged.remove(token);
        }

    private:
        int32_t region = 0;
        int32_t buildingNumber = 0;
        int32_t floor = 0;
        int32_t roomNumber = 0;

        int32_t startDateYear = 0;
        int32_t startDateMonth = 0;

        event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged {};
    };
}

namespace winrt::Heyiwei2::Models::factory_implementation
{
    struct DormInfo : DormInfoT<DormInfo, implementation::DormInfo>
    {};
}