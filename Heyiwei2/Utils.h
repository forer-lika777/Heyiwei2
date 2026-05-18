#pragma once
#include <string>
#include <iostream>
#include <algorithm>

#include "Models.Student.h"
#include "Models.WaterRecord.h"

class Utils
{
public:
	//计算总水费
	static double calculateTotalWaterFee(double const& usage);
	//检验学生ID是否合法
	static bool validateStudentId(winrt::Heyiwei2::Models::Student const& record);
	//检测水费记录是否合法
	static bool validateWaterRecord(winrt::Heyiwei2::Models::WaterRecord const& record);
	//排序水费记录
	static void sortWaterRecords(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Heyiwei2::Models::WaterRecord>& records);

	static int32_t getCurrentYear();

	static int32_t getCurrentMonth();

	static std::vector<int32_t> generateThisYearMonths();

	static std::vector<int32_t> generatePastYearMonths();

	static std::vector<int32_t> generateYears(int32_t const& count);
};

