#pragma once
#include "Models.WaterRecord.h"
#include "Models.Result.h"

using namespace winrt::Windows::Foundation::Collections;

class RecordManager
{
private:
    IObservableVector<winrt::Heyiwei2::Models::implementation::WaterRecord>& waterRecords;
public:
    RecordManager(IObservableVector<winrt::Heyiwei2::Models::implementation::WaterRecord>& records);

    winrt::Heyiwei2::Models::implementation::Result addWaterRecord(winrt::Heyiwei2::Models::implementation::WaterRecord const& record);
    winrt::Heyiwei2::Models::implementation::Result removeWaterRecord(int year, int month);
    winrt::Heyiwei2::Models::implementation::Result updateWaterRecord(int year, int month, double usage);
    int32_t querySpecificWaterRecord(int year, int month);
};

