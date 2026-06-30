#pragma once

#include "EditStudentForm.g.h"

namespace winrt::Heyiwei2::implementation {
	struct EditStudentForm : EditStudentFormT<EditStudentForm> {
	public:
		EditStudentForm() {}

		hstring Name();
		void Name(hstring const& name);
		hstring StudentId();
		void StudentId(hstring const& studentId);

		void LockStudentId();

		void showInfo(hstring const& info);
	};
}

namespace winrt::Heyiwei2::factory_implementation {
	struct EditStudentForm : EditStudentFormT<EditStudentForm, implementation::EditStudentForm> {};
}
