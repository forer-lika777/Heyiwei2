#include "pch.h"
#include "Models.Dorm.h"
#include "Models.Dorm.g.cpp"
#include "Utils.h"

using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Foundation;

namespace winrt::Heyiwei2::Models::implementation {
	IObservableVector<IInspectable> Dorm::Students() {
		return students;
	}

	void Dorm::Students(IObservableVector<IInspectable> const& value) {
		students = value;
	}

	IObservableVector<IInspectable> Dorm::Records() {
		return records;
	}

	void Dorm::Records(IObservableVector<IInspectable> const& value) {
		records = value;
	}

	winrt::Heyiwei2::Models::DormInfo Dorm::Info() {
		return info;
	}

	void Dorm::Info(winrt::Heyiwei2::Models::DormInfo const& value) {
		if (info != value) {

			completeMonths(value);

			info = value;
			
			propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"Info"));
		}

		hstring id = Utils::generateDormId(info);
		if (dormId != id) {
			propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"DormId"));
			dormId = id;
		}
	}

	hstring Dorm::DormId() {
		return dormId;
	}

	void Dorm::completeMonths(winrt::Heyiwei2::Models::DormInfo const& value) {
		int endYear, endMonth;

		if (info == nullptr || records.Size() == 0 || info.StartDateYear() == 0 || info.StartDateMonth() == 0) {
			endYear = Utils::getCurrentYear();
			endMonth = Utils::getCurrentMonth();
		}
		else if (value.StartDateYear() < info.StartDateYear() || value.StartDateMonth() < info.StartDateMonth()) {
			auto r = records.GetAt(records.Size() - 1).as<winrt::Heyiwei2::Models::WaterRecord>(); // pretending that the last record is the oldest one
			endYear = r.Year();
			endMonth = r.Month() - 1;
		}
		else return;

		for (int currentYear = endYear; currentYear >= value.StartDateYear(); currentYear--) {
			int currentYearStartMonth = currentYear == value.StartDateYear() ? value.StartDateMonth() : 1;
			int currentYearEndMonth = currentYear == endYear ? endMonth : 12;

			for (int currentMonth = currentYearEndMonth; currentMonth >= currentYearStartMonth; currentMonth--) {

				auto record = winrt::make<winrt::Heyiwei2::Models::implementation::WaterRecord>();

				record.Year(currentYear);
				record.Month(currentMonth);

				records.Append(record);
			}
		}
	}

	//winrt::Heyiwei2::Models::WaterRecord Dorm::getEarliestRecordDate() {
	//	//int32_t year, month;

	//	//winrt::Heyiwei2::Models::WaterRecord record;
	//	//for (auto r : records) {
	//	//	
	//	//}
	//}
}
