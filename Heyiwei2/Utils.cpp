#include "pch.h"
#include "Utils.h"
#include "Models.WaterRecord.h"
#include "Models.Student.h" 

void Utils::calculateTotalWaterFee(winrt::Heyiwei2::Models::implementation::WaterRecord& record)
{
    record.Cost(record.Usage() * 24.5);
}

bool Utils::validateStudentId(winrt::Heyiwei2::Models::implementation::Student const& record)
{
    // StudentId() 返回 winrt::hstring，record 是 const 引用，使用 const_cast 调用非 const 成员以修复匹配错误
    winrt::hstring hId = const_cast<winrt::Heyiwei2::Models::implementation::Student&>(record).StudentId();
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

bool Utils::validateWaterRecord(winrt::Heyiwei2::Models::implementation::WaterRecord const& record){

	int i = 0;
	winrt::hstring studentId = student.StudentId();
	if (studentId.size() != 10)
	{
		return false;
	}
	else
	{
		while (i < studentId.size())
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
}
bool Utils::validateWaterRecord(winrt::Heyiwei2::Models::WaterRecord const& record)
{
    // record 是 const 引用，直接使用 const_cast 获取可变引用以调用非 const 成员，避免拷贝（拷贝构造被删除）
    auto& r = const_cast<winrt::Heyiwei2::Models::implementation::WaterRecord&>(record);

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

void Utils::sortWaterRecords(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Heyiwei2::Models::implementation::WaterRecord>& records)
{
    uint32_t n = records.Size();
    std::vector<winrt::Heyiwei2::Models::implementation::WaterRecord> vec;
    vec.reserve(n);

    for (uint32_t i = 0; i < n; ++i)
    {
        vec.push_back(records.GetAt(i));
    }

    std::sort(vec.begin(), vec.end(),
        [](const winrt::Heyiwei2::Models::implementation::WaterRecord& a, const winrt::Heyiwei2::Models::implementation::WaterRecord& b)
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