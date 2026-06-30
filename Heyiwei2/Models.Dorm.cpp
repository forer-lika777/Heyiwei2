#include "pch.h"
#include "Models.Dorm.h"
#include "Models.Dorm.g.cpp"
#include "Utils.h"

namespace winrt::Heyiwei2::Models::implementation {

	IObservableVector<IInspectable> Dorm::Students() {
		return students;
	}

	void Dorm::Students(IObservableVector<winrt::Windows::Foundation::IInspectable> const& value) {
		students = value;
		RefreshStudentsCount();
	}

	IObservableVector<IInspectable> Dorm::Records() {
		return records;
	}

	void Dorm::Records(IObservableVector<winrt::Windows::Foundation::IInspectable> const& value) {
		records = value;
		RefreshStatus();
		RefreshRecordsCount();
	}

	winrt::Heyiwei2::Models::DormInfo Dorm::Info() {
		return info;
	}

	void Dorm::Info(winrt::Heyiwei2::Models::DormInfo const& value) {
		if (SetProperty(info, value, L"Info")) {
			completeMonths(value);
			RefreshRecordsCount();
		}

		dormId = Utils::generateDormId(info);
		RaisePropertyChanged(L"DormId");
		//SetProperty(dormId, id, L"DormId");
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

	uint32_t Dorm::StudentsCount() const {
		return studentsCount;
	}

	uint32_t Dorm::RecordsCount() const {
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
				if (cost == 0.0) {
					record.HasPaid(true);
					continue;
				}
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
		RaisePropertyChanged(L"Status");
		RaisePropertyChanged(L"Surplus");
		RaisePropertyChanged(L"Arrears");
	}

	void Dorm::RefreshStudentsCount() {
		SetProperty(studentsCount, students.Size(), L"StudentsCount");
	}

	void Dorm::RefreshRecordsCount() {
		SetProperty(recordsCount, records.Size(), L"RecordsCount");
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
