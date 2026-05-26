#include "pch.h"
#include "Models.WaterRecord.h"
#include "Models.WaterRecord.g.cpp"

namespace winrt::Heyiwei2::Models::implementation {
	int32_t WaterRecord::Year() const {
		return year;
	}

	void WaterRecord::Year(int32_t value) {
		if (year != value) {
			year = value;
			propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"Year"));
		}
	}

	int32_t WaterRecord::Month() const {
		return month;
	}

	void WaterRecord::Month(int32_t value) {
		if (month != value) {
			month = value;
			propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"Month"));
		}
	}

	double WaterRecord::Usage() const {
		return usage;
	}

	void WaterRecord::Usage(double value) {
		if (usage != value) {
			usage = value;
			propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"Usage"));
		}
	}

	double WaterRecord::Cost() const {
		return cost;
	}

	void WaterRecord::Cost(double value) {
		if (cost != value) {
			cost = value;
			HasPaid((cost <= 0.0) ? true : false);
			propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"Cost"));
		}
	}

	bool WaterRecord::HasPaid() const {
		return hasPaid;
	}

	void WaterRecord::HasPaid(bool value) {
		if (hasPaid != value) {
			hasPaid = value;
			propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"HasPaid"));
		}
	}
}
