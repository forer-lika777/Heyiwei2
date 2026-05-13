#pragma once
#include "Models.Student.h"
#include "Models.Result.h"

using namespace winrt::Heyiwei2::Models;
using namespace Heyiwei2::Models;

namespace Heyiwei2::Interfaces {
	class IDormManager {
	public:
		virtual std::vector<Student> getAllStudents() = 0;
		virtual Result addStudent(const Student& student) = 0;
		virtual Result removeStudent(const winrt::hstring& id) = 0;
		virtual Result updateStudentName(const winrt::hstring& id, const winrt::hstring& name) = 0;
		
	};
}