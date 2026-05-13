#pragma once
#include "Models.WaterRecord.h"
#include "Models.Result.h"

using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Heyiwei2::Models;
using namespace Heyiwei2::Models;

class RecordManager
{
private:
    IObservableVector<WaterRecord>& waterRecords;
public:
    RecordManager(IObservableVector<WaterRecord>& records);

    Result addWaterRecord(WaterRecord const& record);
    Result removeWaterRecord(int year, int month);
    Result updateWaterRecord(int year, int month, double usage);
    int32_t querySpecificWaterRecord(int year, int month);
};

