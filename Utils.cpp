// Heyiwei2/Utils.h
#pragma once
#include <string>
#include <vector>
#include <algorithm>

#include "Models.Student.h"
#include "Models.WaterRecord.h"
#include <winrt/Windows.Foundation.Collections.h>

class Utils
{
public:
	// 计算总水费
	static void calculateTotalWaterFee(winrt::Heyiwei2::Models::WaterRecord& record);
	// 检验学生ID是否合法
	static bool validateStudentId(winrt::Heyiwei2::Models::Student const& record);
	// 检测水费记录是否合法
	static bool validateWaterRecord(winrt::Heyiwei2::Models::WaterRecord const& record);
	// 排序水费记录
	static void sortWaterRecords(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Heyiwei2::Models::WaterRecord>& records);
};


// Heyiwei2/Utils.cpp
#include "pch.h"
#include "Utils.h"

void Utils::calculateTotalWaterFee(winrt::Heyiwei2::Models::WaterRecord& record)
{
    record.Cost(record.Usage() * 24.5);
}

bool Utils::validateStudentId(winrt::Heyiwei2::Models::Student const& record)
{
    winrt::hstring hId = record.StudentId();
    std::wstring studentId(hId.c_str());

    if (studentId.length() != 10)
    {
        return false;
    }

    for (size_t i = 0; i < studentId.length(); ++i)
    {
        wchar_t c = studentId[i];
        if (c < L'0' || c > L'9')
        {
            return false;
        }
    }

    return true;
}

bool Utils::validateWaterRecord(winrt::Heyiwei2::Models::WaterRecord const& record)
{
    int year = record.Year();
    int month = record.Month();
    double usage = record.Usage();

    if (year < 2026)
    {
        return false;
    }
    else if (month < 1 || month > 12)
    {
        return false;
    }
    else if (usage < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

void Utils::sortWaterRecords(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Heyiwei2::Models::WaterRecord>& records)
{
    uint32_t n = records.Size();
    std::vector<winrt::Heyiwei2::Models::WaterRecord> vec;
    vec.reserve(n);

    for (uint32_t i = 0; i < n; ++i)
    {
        vec.push_back(records.GetAt(i));
    }

    std::sort(vec.begin(), vec.end(),
        [](const winrt::Heyiwei2::Models::WaterRecord& a, const winrt::Heyiwei2::Models::WaterRecord& b)
        {
            if (a.Year() != b.Year())
            {
                return a.Year() < b.Year();
            }
            return a.Month() < b.Month();
        });

    records.Clear();
    for (auto const& item : vec)
    {
        records.Append(item);
    }
}