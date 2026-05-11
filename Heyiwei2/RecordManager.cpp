#include "pch.h"
#include "RecordManager.h"
#include <algorithm>

//初始化RecordManager，传入水费记录
RecordManager::RecordManager(std::vector<WaterRecord>& records)
    : waterRecords(records) {
}

//添加水费记录，检查是否已存在相同年月的记录
Result RecordManager::addWaterRecord(const WaterRecord& record) {
    for (const auto& r : waterRecords) {
        if (r.year == record.year && r.month == record.month) {
            return Result(false, "记录已存在");
        }
    }
    waterRecords.push_back(record);
    return Result(true, "添加成功");
}

//根据年月删除水费记录
void RecordManager::removeWaterRecord(int year, int month) {
    waterRecords.erase(
        std::remove_if(waterRecords.begin(), waterRecords.end(),
            [year, month](const WaterRecord& r) {
                return r.year == year && r.month == month;
            }),
        waterRecords.end());
}

//根据年月更新水费记录的用量
void RecordManager::updateWaterRecord(int year, int month, double usage) {
    for (auto& r : waterRecords) {
        if (r.year == year && r.month == month) {
            r.usage = usage;
            break;
        }
    }
}

//根据年月查询水费记录，返回符合条件的记录列表
std::vector<WaterRecord> RecordManager::queryWaterRecord(int year, int month) {
    std::vector<WaterRecord> result;
    for (const auto& r : waterRecords) {
        if (r.year == year && r.month == month) {
            result.push_back(r);
        }
    }
    return result;
}

//根据年月查询特定的水费记录，返回指向该记录的指针，如果未找到则返回nullptr
WaterRecord* RecordManager::querySpecificWaterRecord(int year, int month) {
    for (auto& r : waterRecords) {
        if (r.year == year && r.month == month) {
            return &r;
        }
    }
    return nullptr;
}