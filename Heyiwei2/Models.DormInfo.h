#pragma once
#include "Models.DormInfo.g.h"
#include <winrt/Windows.UI.Xaml.Data.h>

namespace winrt::Heyiwei2::Models::implementation
{
    struct DormInfo : DormInfoT<DormInfo, winrt::Windows::UI::Xaml::Data::INotifyPropertyChanged>
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

        winrt::event<winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged;

        // 实现 INotifyPropertyChanged
        winrt::event_token PropertyChanged(
            winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
        {
            return propertyChanged.add(handler);
        }

        void PropertyChanged(winrt::event_token const& token)
        {
            propertyChanged.remove(token);
        }

        // 辅助方法：触发属性变更
        void RaisePropertyChanged(hstring const& propertyName)
        {
            propertyChanged(*this,
                winrt::Windows::UI::Xaml::Data::PropertyChangedEventArgs(propertyName));
        }

    private:
        int32_t region = 0;
        int32_t buildingNumber = 0;
        int32_t floor = 0;
        int32_t roomNumber = 0;

        int32_t startDateYear = 0;
        int32_t startDateMonth = 0;
    };
}
