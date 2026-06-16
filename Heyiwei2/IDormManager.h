#pragma once
#include "Models.Student.h"
#include "Models.Result.h"

using winrt::Windows::Foundation::Collections::IObservableVector;
using winrt::Windows::Foundation::IInspectable;
using namespace winrt::Heyiwei2::Models;

namespace Interfaces {
	class IDormManager {
	public:
		virtual IObservableVector<IInspectable> getAllStudents() = 0;
		virtual Result addStudent(const Student& student) = 0;
		virtual Result removeStudent(const winrt::hstring& id) = 0;
		virtual Result updateStudentName(const winrt::hstring& id, const winrt::hstring& name) = 0;
	};
}