#pragma once
#include <vector>
#include "Models.Result.h"
#include "IMainManager.h"

using namespace winrt::Heyiwei2::Models;

class MainManager : Interfaces::IMainManager
{
private:
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>& dorms;

public:
	MainManager(winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>& dorms) : dorms(dorms) {}
	const winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>& getAllDorms();
    // --- 学生管理 ---
    Result addStudent(Student const& student) override;
    Result removeStudent(const winrt::hstring& id) override;
    Result updateStudent(const winrt::hstring& id, const winrt::hstring& name) override;

    // --- 宿舍管理 ---
    Result addDorm(Dorm const& dorm) override;
    Result removeDorm(int index) override;
    Result updateDorm(int index, Dorm const& dorm) override;

    // --- 学生分配 ---
    Result assignStudentToDorm(int dormIndex, const winrt::hstring& studentId) override;
    Result removeStudentFromDorm(int dormIndex, const winrt::hstring& studentId) override;

    // --- 水费记录 ---
    Result addWaterRecord(int dormIndex, WaterRecord const& record) override;
    Result removeWaterRecord(int dormIndex, int year, int month) override;
    Result updateWaterRecord(int dormIndex, int year, int month, double usage) override;

};

