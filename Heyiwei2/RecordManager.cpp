#include "pch.h"
#include "RecordManager.h"
#include <algorithm>
#include "Models.Result.h"
#include "Models.WaterRecord.h"
#include "Utils.h"

using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Heyiwei2::Models;


//初始化RecordManager，传入水费记录
RecordManager::RecordManager(IObservableVector<IInspectable> records)
	: waterRecords(records) {}

//添加水费记录，检查是否已存在相同年月的记录
Result RecordManager::addWaterRecord(const WaterRecord& record) {
	auto r = querySpecificWaterRecord(record.Year(), record.Month());
	if (r != -1) {
		return winrt::make<implementation::Result>(false, L"添加失败：不可添加具有相同年月份的记录");
	}
	auto result = Utils::validateWaterRecord(record);
	if (!result.Success()) return result;
	waterRecords.Append(record);
	return winrt::make<implementation::Result>(true, L"添加成功");
}

//根据年月删除水费记录
Result RecordManager::removeWaterRecord(int year, int month) {
	auto r = querySpecificWaterRecord(year, month);
	if (r == -1) {
		return winrt::make<implementation::Result>(false, L"删除失败：未找到记录");
	}
	waterRecords.RemoveAt(r);
	return winrt::make<implementation::Result>(true, L"删除成功");
}

//根据年月更新水费记录的用量
Result RecordManager::updateWaterRecord(int year, int month, double usage) {
	auto r = querySpecificWaterRecord(year, month);
	if (r == -1) {
		return winrt::make<implementation::Result>(false, L"更新失败：未找到记录");
	}
	waterRecords.GetAt(r).as<WaterRecord>().Usage(usage);
	return winrt::make<implementation::Result>(true, L"更新成功");
}

//根据年月查询特定的水费记录，返回指向该记录的索引，如果未找到则返回-1
int32_t RecordManager::querySpecificWaterRecord(int year, int month) {
	for (uint32_t i = 0; i < waterRecords.Size(); i++) {
		auto r = waterRecords.GetAt(i).as<WaterRecord>();
		if (r.Year() == year && r.Month() == month) {
			return i;
		}
	}
	return -1;
}