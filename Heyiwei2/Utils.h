#pragma once
#include <algorithm>

#include "Models.Dorm.h"
#include "Models.Result.h"
#include "Models.Student.h"
#include "Models.WaterRecord.h"

using winrt::Windows::Foundation::Collections::IObservableVector;
using winrt::Windows::Foundation::IInspectable;
using winrt::Heyiwei2::Models::Dorm;
using winrt::Heyiwei2::Models::DormInfo;
using winrt::Heyiwei2::Models::Result;
using winrt::Heyiwei2::Models::Student;
using winrt::Heyiwei2::Models::WaterRecord;

class Utils {
public:
	//计算总水费
	static double calculateTotalWaterFee(double const& usage);

	static winrt::Heyiwei2::Models::Result valideDormInfo(winrt::Heyiwei2::Models::DormInfo const& dormInfo);
	//检验学生ID是否合法
	static winrt::Heyiwei2::Models::Result validateStudent(winrt::Heyiwei2::Models::Student const& record);
	//检测水费记录是否合法
	static winrt::Heyiwei2::Models::Result validateWaterRecord(winrt::Heyiwei2::Models::WaterRecord const& record);
	//排序水费记录
	static void sortWaterRecords(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> records);

	static int32_t getCurrentYear();

	static int32_t getCurrentMonth();

	static std::vector<int32_t> generateThisYearMonths();

	static std::vector<int32_t> generatePastYearMonths();

	static std::vector<int32_t> generateYears(int32_t const& count);

	static winrt::hstring generateDormId(winrt::Heyiwei2::Models::DormInfo info);
};

