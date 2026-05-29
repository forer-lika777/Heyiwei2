#pragma once
#include "Models.WaterRecord.g.h"

namespace winrt::Heyiwei2::Models::implementation
{
    struct WaterRecord : WaterRecordT<WaterRecord>
    {
    public:
        WaterRecord() = default;

        int32_t Year() const;
        void Year(int32_t value);

        int32_t Month() const;
        void Month(int32_t value);

        double Usage() const;
        void Usage(double value);

        double Cost() const;
        void Cost(double value);

        bool HasPaid() const;
        void HasPaid(bool value);

        winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler) {
            return propertyChanged.add(handler);
        }

        void PropertyChanged(winrt::event_token const& token) noexcept {
            propertyChanged.remove(token);
        }

    private:
		int32_t year = 0;
		int32_t month = 0;
		double usage = 0.0;
        double cost = 0.0;
		bool hasPaid = true;

        event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged{};
    };
}

namespace winrt::Heyiwei2::Models::factory_implementation
{
    struct WaterRecord : WaterRecordT<WaterRecord, implementation::WaterRecord> {

    };
}