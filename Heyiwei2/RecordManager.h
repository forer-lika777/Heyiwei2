#pragma once
#include "Models.Result.h"
#include "Models.WaterRecord.h"

using winrt::Heyiwei2::Models::Result;
using winrt::Heyiwei2::Models::WaterRecord;

class RecordManager
{
private:
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> waterRecords;
public:
    RecordManager() = default;

    Result addWaterRecord(winrt::Heyiwei2::Models::WaterRecord const& record);
    Result removeWaterRecord(int year, int month);
    Result updateWaterRecord(int year, int month, double usage);

    int32_t querySpecificWaterRecord(int year, int month);

    void setRecords(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> records);
};