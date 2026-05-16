#include "pch.h"
#include "Models.WaterRecord.h"
#include "Models.WaterRecord.g.cpp"

namespace winrt::Heyiwei2::Models::implementation
{
    int32_t WaterRecord::Year()
    {
        return year;
    }
    void WaterRecord::Year(int32_t value)
    {
        if (year != value) {
            year = value;
        }
    }
    int32_t WaterRecord::Month()
    {
        return month;
    }
    void WaterRecord::Month(int32_t value)
    {
        if (month != value) {
            month = value;
        }
    }
    double WaterRecord::Usage()
    {
        return usage;
    }
    void WaterRecord::Usage(double value)
    {
        if (usage != value) {
            usage = value;
        }
    }
    double WaterRecord::Cost()
    {
        return cost;
    }
    void WaterRecord::Cost(double value)
    {
        if (cost != value) {
            cost = value;
        }
    }
    bool WaterRecord::HasPaid()
    {
        return hasPaid;
    }
    void WaterRecord::HasPaid(bool value)
    {
        if (hasPaid != value) {
            hasPaid = value;
        }
    }
}
