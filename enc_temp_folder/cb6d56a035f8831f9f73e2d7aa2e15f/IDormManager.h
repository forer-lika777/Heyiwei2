#pragma once
#include "Models.h"

namespace Heyiwei2::Interfaces {
	class IDormManager {
	public:
		virtual std::vector<Models::Student> getAllStudents() = 0;
		virtual Models::Result addStudent(const Models::Student& student) = 0;
		virtual Models::Result removeStudent(const winrt::hstring& id) = 0;
		virtual Models::Result updateStudentName(const winrt::hstring& id, const winrt::hstring& name) = 0;
		
	};
}