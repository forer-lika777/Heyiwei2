#pragma once
#include "Models.h"

using namespace Models;

class RecordManager
{
private:
    std::vector<WaterRecord>& waterRecords;

public:
    RecordManager(std::vector<WaterRecord>& records);

    Result addWaterRecord(const WaterRecord& record);
    void removeWaterRecord(int year, int month);
    void updateWaterRecord(int year, int month, double usage);
    std::vector<WaterRecord> queryWaterRecord(int year, int month);
    WaterRecord* querySpecificWaterRecord(int year, int month);
};

