#pragma once
#include "Models.h"

class RecordManager
{
    private:
    std::vector<Models::WaterRecord>& waterRecords;

public:
    RecordManager(std::vector<Models::WaterRecord>& records);

    Models::Result addWaterRecord(const Models::WaterRecord& record);
    void removeWaterRecord(int year, int month);
    void updateWaterRecord(int year, int month, double usage);
    std::vector<Models::WaterRecord> queryWaterRecord(int year, int month);
    Models::WaterRecord* querySpecificWaterRecord(const std::string& id, int year, int month);
};

