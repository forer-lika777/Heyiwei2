#pragma once
#include "Models.Dorm.g.h"
#include "Models.WaterRecord.h"

#include "Models.BindableBase.h"

namespace winrt::Heyiwei2::Models::implementation {
	struct Dorm : DormT<Dorm, winrt::Heyiwei2::Models::implementation::BindableBase> {
	public:
		Dorm() = default;

		winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> Students();
		void Students(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> const& value);

		winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> Records();
		void Records(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> const& value);

		winrt::Heyiwei2::Models::DormInfo Info();
		void Info(winrt::Heyiwei2::Models::DormInfo const& value);

		bool Status() const;
		double Arrears() const;
		double Surplus() const;

		uint32_t StudentsCount() const;
		uint32_t RecordsCount() const;

		hstring DormId();

		void RefreshStatus();
		void RefreshStudentsCount();
		void RefreshRecordsCount();

		winrt::event_token PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler) {
			return propertyChanged.add(handler);
		}
		void PropertyChanged(winrt::event_token const& token) noexcept {
			propertyChanged.remove(token);
		}

	private:
		winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> students{ winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>() };
		winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> records{ winrt::single_threaded_observable_vector<winrt::Windows::Foundation::IInspectable>() };

		hstring dormId;
		winrt::Heyiwei2::Models::DormInfo info;

		bool status = true;
		double arrears = 0.0;
		double surplus = 0.0;

		uint32_t studentsCount = 0;
		uint32_t recordsCount = 0;

		void completeMonths(winrt::Heyiwei2::Models::DormInfo const& info);

		winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged;
	};
}

namespace winrt::Heyiwei2::Models::factory_implementation {
	struct Dorm : DormT<Dorm, implementation::Dorm> {};
}