#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
class Utils
{
public:
	//计算总水费
	static double calculateTotalWaterFee(Heyiwei2::Models::WaterRecord const& record);
	//检验学生ID是否合法
	static bool validateStudentId(Heyiwei2::Models::Student const& record);
	//检测水费记录是否合法
	static bool validateWaterRecord(Heyiwei2::Models::WaterRecord const& record);
	//排序水费记录
	static void sortWaterRecords(vector<Heyiwei2::Models::WaterRecord>& records);

};

