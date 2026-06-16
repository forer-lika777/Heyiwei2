#include "pch.h"
#include "Models.Dorm.h"
#include "Models.Dorm.g.cpp"
#include "Utils.h"

namespace winrt::Heyiwei2::Models::implementation {

	IObservableVector<IInspectable> Dorm::Students() {
		return students;
	}

	void Dorm::Students(IObservableVector<IInspectable> const& value) {
		students = value;
		RefreshStudentsCount();
	}

	IObservableVector<IInspectable> Dorm::Records() {
		return records;
	}

	void Dorm::Records(IObservableVector<IInspectable> const& value) {
		records = value;
		RefreshStatus();
		RefreshRecordsCount();
	}

	winrt::Heyiwei2::Models::DormInfo Dorm::Info() {
		return info;
	}

	void Dorm::Info(winrt::Heyiwei2::Models::DormInfo const& value) {
		if (info != value) {
			completeMonths(value);

			info = value;
			propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"Info"));
			RefreshRecordsCount();
		}

		hstring id = Utils::generateDormId(info);
		if (dormId != id) {
			dormId = id;
			propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"DormId"));
		}
	}

	bool Dorm::Status() const {
		return status;
	}

	double Dorm::Arrears() const {
		return arrears;
	}

	double Dorm::Surplus() const {
		return surplus;
	}

	int32_t Dorm::StudentsCount() const {
		return studentsCount;
	}

	int32_t Dorm::RecordsCount() const {
		return recordsCount;
	}

	hstring Dorm::DormId() {
		return dormId;
	}

	void Dorm::RefreshStatus() {
		arrears = 0.0;
		for (auto r : records) {
			auto record = r.as<winrt::Heyiwei2::Models::WaterRecord>();
			if (!record.HasPaid()) {
				auto cost = record.Cost();
				if (surplus > 0.0) {
					if (surplus >= cost) {
						surplus -= cost;
						record.HasPaid(true);
					}
					else {
						arrears += cost - surplus;
						surplus = 0.0;
					}
				}
				else {
					arrears += cost;
				}
			}
		}
		if (arrears > 0.0) status = false;
		else status = true;
		propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"Status"));
		propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"Surplus"));
		propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"Arrears"));
	}

	void Dorm::RefreshStudentsCount() {
		if (studentsCount != students.Size()) {
			studentsCount = students.Size();
			propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"StudentsCount"));
		}
	}

	void Dorm::RefreshRecordsCount() {
		if (recordsCount != records.Size()) {
			recordsCount = records.Size();
			propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"RecordsCount"));
		}
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
}
