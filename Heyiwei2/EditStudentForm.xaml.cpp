#include "pch.h"
#include "EditStudentForm.xaml.h"
#if __has_include("EditStudentForm.g.cpp")
#include "EditStudentForm.g.cpp"
#endif

using namespace winrt::Microsoft::UI::Xaml;

namespace winrt::Heyiwei2::implementation {
	hstring EditStudentForm::Name() {
		return NameEntryTextBox().Text();
	}

	void EditStudentForm::Name(hstring const& name) {
		NameEntryTextBox().Text(name);
	}

	hstring EditStudentForm::StudentId() {
		return StudentIdEntryTextBox().Text();
	}

	void EditStudentForm::StudentId(hstring const& studentId) {
		StudentIdEntryTextBox().Text(studentId);
	}

	void EditStudentForm::showInfo(hstring const& info) {
		OutputInfoTextBlock().Text(info);
	}
}
