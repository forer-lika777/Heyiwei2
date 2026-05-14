#pragma once
#include <string>
#include <iostream>
#include <algorithm>
#include "Models.WaterRecord.h"
#include "Models.Student.h"

using namespace winrt::Heyiwei2::Models;

class Utils
{
public:
	//计算总水费
	static void calculateTotalWaterFee(WaterRecord const& record);
	//检验学生ID是否合法
	static bool validateStudentId(Student const& student);
	//检测水费记录是否合法
	static bool validateWaterRecord(WaterRecord const& record);
	//排序水费记录
	static void sortWaterRecords(winrt::Windows::Foundation::Collections::IObservableVector<WaterRecord>& records);
};

