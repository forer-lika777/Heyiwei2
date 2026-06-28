// MainManager.h
#pragma once
#include "IMainManager.h"
#include "DormManager.h"

#include "Models.Dorm.h"
#include "Models.Result.h"
#include "Models.Student.h"

using winrt::hstring;
using namespace winrt::Heyiwei2::Models;

class MainManager : public Interfaces::IMainManager
{
public:
    MainManager(IObservableVector<IInspectable>& dorms);
    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> getDormItems();

    Dorm getDorm(hstring const& dormId) override;

    void SaveCurrentData() override;
    void LoadStoredData() override;

    // 学生管理
    Result addStudent(hstring const& dormId, Student const& student) override;
    Result removeStudent(hstring const& dormId, hstring const& studentId) override;
    Result updateStudent(hstring const& dormId, hstring const& studentId, Student const& student) override;

    // 宿舍管理
    Result addDorm(Dorm const& dorm) override;
    Result removeDorm(hstring const& dormId) override;
    Result updateDorm(hstring const& dormId, Dorm const& dorm) override;
    Result updateDormInfo(hstring const& dormId, DormInfo const& info) override;

    // 学生分配
    //Result addStudentToDorm(hstring const& dormId, hstring const& studentId) override;
    //Result removeStudentFromDorm(hstring const& dormId, hstring const& studentId) override;
    //Result updateStudentInDorm(hstring const& dormId, hstring const& studentId, const Student student) override;

    // 水费记录
    Result addWaterRecord(hstring const& dormId, WaterRecord const& record) override;
    Result removeWaterRecord(hstring const& dormId, int year, int month) override;
    Result updateWaterRecord(hstring const& dormId, int year, int month, WaterRecord const& record) override;

private:
    IObservableVector<IInspectable> dorms;
    DormManager dormManager;

    //DormManager* getDormManager(hstring const& dormId);
    int32_t findDormIndex(hstring const& dormId);
};