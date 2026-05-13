#include "pch.h"
#include "Utils.h"
#include "Models.WaterRecord.h"

using namespace winrt::Heyiwei2::Models::implementation;
void Utils::calculateTotalWaterFee(WaterRecord& record)
{
	record.Cost(record.Usage() * 24.5);
}
bool Utils::validateStudentId(Student const& record)
{
	int i = 0;
	std::string studentId = record.StudentId;
	if (studentId.length() != 10)
	{
		return false;
	}
	else
	{
		while (i < studentId.length())
		{
			int jiance = studentId[i];
			if (jiance < '0' || jiance > '9')
			{
				return false;
				break;
			}
			i = i + 1;
		}
		return true;
	}
bool Utils::validateWaterRecord(WaterRecord const& record)
{
	if (record.Year < 2026)
	{
		return false;
	}
	else if (record.Month < 1 || record.Month > 12)
	{
		return false;
	}
	else if (record.Usage < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}
void Utils::sortWaterRecords(std::vector<WaterRecord>& records)
{
	std::sort(records.begin(), records.end(),
		[](const WaterRecord& a, const WaterRecord& b)
		{
			if (a.Year() != b.Year())
			{
				return a.Year() < b.Year();
			}

			return a.Month() < b.Month();
		});
}