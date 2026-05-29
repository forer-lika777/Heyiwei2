#pragma once
#include "Models.Student.h"
#include "Models.Dorm.h"
#include "Models.WaterRecord.h"
#include "Models.Result.h"

using namespace winrt::Heyiwei2::Models;
using winrt::hstring;

namespace Interfaces
{
	class IMainManager
	{
	public:
		virtual winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> getDormItems() = 0;

		virtual Dorm getDorm(const hstring dormId) = 0;

		virtual void LoadStoredData() = 0;
		virtual void SaveCurrentData() = 0;

		virtual Result addStudent(const hstring dormId, Student const student) = 0;
		virtual Result removeStudent(const hstring dormId, const hstring studentId) = 0;
		virtual Result updateStudent(const hstring dormId, const hstring studentId, Student const student) = 0;

		virtual Result addDorm(const Dorm dorm) = 0;
		virtual Result removeDorm(const hstring dormId) = 0;
		virtual Result updateDorm(const hstring dormId, const Dorm dorm) = 0;
		virtual Result updateDormInfo(const hstring dormId, const DormInfo info) = 0;

		virtual Result addWaterRecord(const hstring dormId, const WaterRecord record) = 0;
		virtual Result removeWaterRecord(const hstring dormId, int year, int month) = 0;
		virtual Result updateWaterRecord(const hstring dormId, int year, int month, const WaterRecord record) = 0;
	};
}