#pragma once
#include "Models.Student.g.h"

namespace winrt::Heyiwei2::Models::implementation {
	struct Student : StudentT<Student> {
	public:
		Student() = default;

		hstring Name();
		void Name(hstring const& value);

		hstring StudentId();
		void StudentId(hstring const& value);

		hstring Password();
		void Password(hstring const& value);

		winrt::event_token PropertyChanged(winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& handler) {
			return propertyChanged.add(handler);
		}

		void PropertyChanged(winrt::event_token const& token) noexcept {
			propertyChanged.remove(token);
		}

	private:
		hstring name;
		hstring studentId;
		hstring password;

		event<winrt::Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> propertyChanged{};
	};
}

namespace winrt::Heyiwei2::Models::factory_implementation {
	struct Student : StudentT<Student, implementation::Student> {};
}