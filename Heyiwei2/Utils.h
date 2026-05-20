#pragma once
#include <algorithm>

class Utils {
public:
	//计算总水费
	static double calculateTotalWaterFee(double const& usage);
	//检验学生ID是否合法
	static winrt::Heyiwei2::Models::Result validateStudent(winrt::Heyiwei2::Models::Student const& record);
	//检测水费记录是否合法
	static winrt::Heyiwei2::Models::Result validateWaterRecord(winrt::Heyiwei2::Models::WaterRecord const& record);
	//排序水费记录
	static void sortWaterRecords(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>& records);

	static int32_t getCurrentYear();

	static int32_t getCurrentMonth();

	static std::vector<int32_t> generateThisYearMonths();

	static std::vector<int32_t> generatePastYearMonths();

	static std::vector<int32_t> generateYears(int32_t const& count);

	static winrt::hstring generateDormId(winrt::Heyiwei2::Models::DormInfo info);
};

