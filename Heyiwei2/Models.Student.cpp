#include "pch.h"
#include "Models.Student.h"
#include "Models.Student.g.cpp"

namespace winrt::Heyiwei2::Models::implementation {
	hstring Student::Name() {
		return name;
	}

	void Student::Name(hstring const& value) {
		if (name != value) {
			name = value;
			propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"Name"));
		}
	}

	hstring Student::StudentId() {
		return studentId;
	}

	void Student::StudentId(hstring const& value) {
		if (studentId != value) {
			studentId = value;
			propertyChanged(*this, Microsoft::UI::Xaml::Data::PropertyChangedEventArgs(L"StudentId"));
		}
	}

	hstring Student::Password() {
		return password;
	}

	void Student::Password(hstring const& value) {
		password = value;
	}
}
