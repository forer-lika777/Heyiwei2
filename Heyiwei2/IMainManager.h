#pragma once
#include "Models.Dorm.h"

using winrt::Windows::Foundation::Collections::IObservableVector;
using winrt::Windows::Foundation::IInspectable;

namespace Interfaces {
	class IMainManager {
	public:
		virtual IObservableVector<IInspectable> getDormItems() = 0;

		virtual Dorm getDorm(hstring const& dormId) = 0;

		virtual void LoadStoredData() = 0;
		virtual void SaveCurrentData() = 0;

		virtual Result addStudent(hstring const& dormId, Student const& student) = 0;
		virtual Result removeStudent(hstring const& dormId, hstring const& studentId) = 0;
		virtual Result updateStudent(hstring const& dormId, hstring const& studentId, Student const& student) = 0;

		virtual Result addDorm(Dorm const& dorm) = 0;
		virtual Result removeDorm(hstring const& dormId) = 0;
		virtual Result updateDorm(hstring const& dormId, Dorm const& dorm) = 0;
		virtual Result updateDormInfo(hstring const& dormId, DormInfo const& info) = 0;

		virtual Result addWaterRecord(hstring const& dormId, WaterRecord const& record) = 0;
		virtual Result removeWaterRecord(hstring const& dormId, int year, int month) = 0;
		virtual Result updateWaterRecord(hstring const& dormId, int year, int month, WaterRecord const& record) = 0;
	};
}