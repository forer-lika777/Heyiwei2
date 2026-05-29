#include "pch.h"
#include "Utils.h"
#include "Models.Result.h"

using namespace winrt::Heyiwei2::Models;

/// <summary>
/// 阶梯计算水费
/// </summary>
/// <param name="usage">用水量</param>
/// <returns>水费</returns>
double Utils::calculateTotalWaterFee(double const& usage) {
	constexpr double tier1Limit = 26.0;
	constexpr double tier2Limit = 34.0;
	constexpr double tier1Price = 2.93;
	constexpr double tier2Price = 4.40;
	constexpr double tier3Price = 7.87;

	if (usage <= tier1Limit) {
		return usage * tier1Price;
	}
	else if (usage <= tier2Limit) {
		return tier1Limit * tier1Price + (usage - tier1Limit) * tier2Price;
	}
	else {
		return tier1Limit * tier1Price + (tier2Limit - tier1Limit) * tier2Price + (usage - tier2Limit) * tier3Price;
	}
}

Result Utils::valideDormInfo(winrt::Heyiwei2::Models::DormInfo const& dormInfo) {
	int32_t roomNumber = dormInfo.RoomNumber();

	if (roomNumber >= 100 || roomNumber <= 0) {
		return winrt::make<implementation::Result>(
			false,
			L"房间号格式有误"
		);
	}

	return winrt::make<implementation::Result>(true, L"");
}

Result Utils::validateStudent(Student const& student) {
	winrt::hstring hId = const_cast<Student&>(student).StudentId();
	std::wstring studentId(hId.c_str());

	if (studentId.size() == 0) {
		return winrt::make<implementation::Result>(false, L"学号不能为空");
	}

	if (student.Name().size() == 0) {
		return winrt::make<implementation::Result>(false, L"姓名不能为空");
	}

	if (studentId.length() != 10) {
		return winrt::make<implementation::Result>(false, L"学号格式错误");
	}

	for (size_t i = 0; i < studentId.length(); ++i) {
		wchar_t c = studentId[i];
		if (c < L'0' || c > L'9') {
			return winrt::make<implementation::Result>(false, L"学号格式错误");
		}
	}

	return winrt::make<implementation::Result>(true, L"");
}

Result Utils::validateWaterRecord(WaterRecord const& record) {
	// record 是 const 引用，直接使用 const_cast 获取可变引用以调用非 const 成员，避免拷贝（拷贝构造被删除）
	auto& r = const_cast<WaterRecord&>(record);

	if (r.Year() > Utils::getCurrentYear()) {
		return winrt::make<implementation::Result>(false, L"年份超出范围");
	}
	else if (r.Month() < 1 || r.Month() > 12) {
		return winrt::make<implementation::Result>(false, L"月份超出范围");
	}
	else if (r.Usage() < 0) {
		return winrt::make<implementation::Result>(false, L"用水量不能为负数");
	}
	else if (record.Usage() > 30000) {
		return winrt::make<implementation::Result>(false, L"你是超人嘛？一个月用 " + winrt::to_hstring(record.Usage()) + L" 吨水？");
	}
	else {
		return winrt::make<implementation::Result>(true, L"");
	}
}

void Utils::sortWaterRecords(IObservableVector<winrt::Windows::Foundation::IInspectable>& records) {
	uint32_t n = records.Size();
	std::vector<WaterRecord> vec;
	vec.reserve(n);

	for (uint32_t i = 0; i < n; ++i) {
		vec.push_back(records.GetAt(i).as<WaterRecord>());
	}

	std::sort(vec.begin(), vec.end(),
		[](const WaterRecord& a, const WaterRecord& b) {
			if (a.Year() != b.Year()) {
				return a.Year() < b.Year();
			}
			return a.Month() < b.Month();
		});

	records.Clear();
	for (auto const& item : vec) {
		records.Append(item);
	}
}

int32_t Utils::getCurrentYear() {
	std::time_t t = std::time(nullptr);
	std::tm now = {};
	localtime_s(&now, &t);
	return now.tm_year + 1900;
}

int32_t Utils::getCurrentMonth() {
	std::time_t t = std::time(nullptr);
	std::tm now = {};
	localtime_s(&now, &t);
	return now.tm_mon + 1;
}

std::vector<int32_t> Utils::generateThisYearMonths() {
	std::vector<int32_t> monthsThisYear;
	int32_t month = Utils::getCurrentMonth();
	for (; month >= 1; month--) {
		monthsThisYear.push_back(month);
	}
	return monthsThisYear;
}

std::vector<int32_t> Utils::generatePastYearMonths() {
	std::vector<int32_t> monthsPastYear;
	for (int32_t i = 12; i >= 1; i--) {
		monthsPastYear.push_back(i);
	}
	return monthsPastYear;
}

std::vector<int32_t> Utils::generateYears(int32_t const& count) {
	std::vector<int32_t> years;
	int32_t year = Utils::getCurrentYear();
	for (int32_t i = 0; i < count; ++i) {
		years.push_back(year);
		year--;
	}
	return years;
}

winrt::hstring Utils::generateDormId(DormInfo info) {
	return L"Dorm-" + winrt::to_hstring(info.Region()) +
		L"-" + winrt::to_hstring(info.BuildingNumber()) +
		L"-" + winrt::to_hstring(info.Floor()) +
		L"-" + winrt::to_hstring(info.RoomNumber());
}
