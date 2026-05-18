#include "pch.h"
#include "Utils.h"
#include "Models.WaterRecord.h"
#include "Models.Student.h" 

double Utils::calculateTotalWaterFee(double const& usage)
{
    constexpr double tier1Limit = 26.0;
    constexpr double tier2Limit = 34.0;
    constexpr double tier1Price = 2.93;
    constexpr double tier2Price = 4.40;
    constexpr double tier3Price = 7.87;

    if (usage <= tier1Limit)
    {
        return usage * tier1Price;
    }
    else if (usage <= tier2Limit)
    {
        return tier1Limit * tier1Price + (usage - tier1Limit) * tier2Price;
    }
    else
    {
        return tier1Limit * tier1Price + (tier2Limit - tier1Limit) * tier2Price + (usage - tier2Limit) * tier3Price;
    }
}

bool Utils::validateStudentId(winrt::Heyiwei2::Models::Student const& record)
{
    // StudentId() 返回 winrt::hstring，record 是 const 引用，使用 const_cast 调用非 const 成员以修复匹配错误
    winrt::hstring hId = const_cast<winrt::Heyiwei2::Models::Student&>(record).StudentId();
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
    // record 是 const 引用，直接使用 const_cast 获取可变引用以调用非 const 成员，避免拷贝（拷贝构造被删除）
    auto& r = const_cast<winrt::Heyiwei2::Models::WaterRecord&>(record);

    if (r.Year() < 2026)
    {
        return false;
    }
    else if (r.Month() < 1 || r.Month() > 12)
    {
        return false;
    }
    else if (r.Usage() < 0)
    {
        return false;
    }
    else
    {
        return true;
    }
	if (record.Year() < 2026)
	{
		return false;
	}
	else if (record.Month() < 1 || record.Month() > 12)
	{
		return false;
	}
	else if (record.Usage() < 0)
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

int32_t Utils::getCurrentYear()
{
    std::time_t t = std::time(nullptr);
    std::tm now = {};
    localtime_s(&now, &t);
    return now.tm_year + 1900;
}

int32_t Utils::getCurrentMonth()
{
    std::time_t t = std::time(nullptr);
    std::tm now = {};
    localtime_s(&now, &t);
    return now.tm_mon + 1;
}

std::vector<int32_t> Utils::generateThisYearMonths()
{
    std::vector<int32_t> monthsThisYear;
    int32_t month = Utils::getCurrentMonth();
    for (; month >= 1; month--) {
        monthsThisYear.push_back(month);
    }
    return monthsThisYear;
}

std::vector<int32_t> Utils::generatePastYearMonths()
{
    std::vector<int32_t> monthsPastYear;
    for (int32_t i = 12; i >= 1; i--) {
        monthsPastYear.push_back(i);
    }
    return monthsPastYear;
}

std::vector<int32_t> Utils::generateYears(int32_t const& count)
{
    std::vector<int32_t> years;
    int32_t year = Utils::getCurrentYear();
    for (int32_t i = 0; i < count; ++i) {
        years.push_back(year);
        year--;
    }
    return years;
}
