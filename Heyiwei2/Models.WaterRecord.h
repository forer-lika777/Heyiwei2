#pragma once
#include "Models.WaterRecord.g.h"

namespace winrt::Heyiwei2::Models::implementation
{
    struct WaterRecord : WaterRecordT<WaterRecord>
    {
    public:
        WaterRecord() = default;

        int32_t Year();
        void Year(int32_t value);
        int32_t Month();
        void Month(int32_t value);
        double Usage();
        void Usage(double value);
        double Cost();
        void Cost(double value);
        bool HasPaid();
        void HasPaid(bool value);

    private:
		int32_t year = 0;
		int32_t month = 0;
		double usage = 0.0;
        double cost = 0.0;
		bool hasPaid = false;
    };
}

namespace winrt::Heyiwei2::Models::factory_implementation
{
    struct WaterRecord : WaterRecordT<WaterRecord, implementation::WaterRecord> {

    };
}