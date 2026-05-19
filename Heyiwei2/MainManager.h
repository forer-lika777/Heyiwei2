// MainManager.h
#pragma once
#include "IMainManager.h"
#include "DormManager.h"
#include <vector>
#include <winrt/Windows.Foundation.Collections.h>

using winrt::hstring;
using winrt::Heyiwei2::Models::Result;
using winrt::Heyiwei2::Models::Dorm;
using winrt::Heyiwei2::Models::Student;
using winrt::Heyiwei2::Models::WaterRecord;
using winrt::Windows::Foundation::Collections::IObservableVector;
using winrt::Windows::Foundation::IInspectable;

class MainManager : public Interfaces::IMainManager
{
public:
    MainManager(IObservableVector<IInspectable>& dorms);

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> getDormItems();
    void saveToJsonFile();
    void TriggerSave(const std::string& filename);
    void TriggerLoad(const std::string& filename);

    Dorm getDorm(const hstring dormId) override;

    // 学生管理
    Result addStudent(const hstring dormId, Student const student) override;
    Result removeStudent(const hstring dormId, const hstring studentId) override;
    Result updateStudent(const hstring dormId, const hstring studentId, const hstring name) override;

    // 宿舍管理
    Result addDorm(const Dorm dorm) override;
    Result removeDorm(const hstring dormId) override;
    Result updateDorm(const hstring dormId, const Dorm dorm) override;
    Result updateDormInfo(const hstring dormId, const DormInfo info) override;

    // 学生分配
    Result addStudentToDorm(const hstring dormId, const hstring studentId) override;
    Result removeStudentFromDorm(const hstring dormId, const hstring studentId) override;
    Result updateStudentInDorm(const hstring dormId, const hstring studentId, const Student student) override;

    // 水费记录
    Result addWaterRecord(const hstring dormId, const WaterRecord record) override;
    Result removeWaterRecord(const hstring dormId, int year, int month) override;
    Result updateWaterRecord(const hstring dormId, int year, int month, const WaterRecord record) override;

private:
    IObservableVector<IInspectable> dorms;
    DormManager dormManager;
    //winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>& dorms;

    //DormManager* getDormManager(const hstring dormId);
    int32_t findDormIndex(const hstring dormId);
};