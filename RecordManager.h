#pragma once
#include <vector>
#include <string>
#include "WaterRecord.h"
#include "Result.h"
#include "DormManager.h"

class RecordManager {
private:
    std::vector<WaterRecord>& waterRecords;
    DormManager& dormManager;

public:
    RecordManager(std::vector<WaterRecord>& records, DormManager& dormMgr);

    Result addWaterRecord(const WaterRecord& record);
    void removeWaterRecord(int year, int month);
    void updateWaterRecord(int year, int month, double usage);
    std::vector<WaterRecord> queryWaterRecord(int year, int month);
    WaterRecord* querySpecificWaterRecord(const std::string& id, int year, int month);
};