#pragma once
#include "Models.Student.h"
#include "Models.Dorm.h"
#include "Models.WaterRecord.h"
#include "Models.Result.h"

using namespace winrt::Heyiwei2::Models;

namespace Interfaces
{
	class IMainManager
	{
	public:
		virtual Result addStudent(Student const& student) = 0;
		virtual Result removeStudent(const winrt::hstring& id) = 0;
		virtual Result updateStudent(const winrt::hstring& id, const winrt::hstring& name) = 0;
		virtual Result addDorm(Dorm const& dorm) = 0;
		virtual Result removeDorm(int index) = 0;
		virtual Result updateDorm(int index, Dorm const& dorm) = 0;
		virtual Result assignStudentToDorm(int dormIndex, const winrt::hstring& studentId) = 0;
		virtual Result removeStudentFromDorm(int dormIndex, const winrt::hstring& studentId) = 0;
		virtual Result addWaterRecord(int dormIndex, WaterRecord const& record) = 0;
		virtual Result removeWaterRecord(int dormIndex, int year, int month) = 0;
		virtual Result updateWaterRecord(int dormIndex, int year, int month, double usage) = 0;
	};
}