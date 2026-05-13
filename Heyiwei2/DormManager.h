#pragma once
#include "IDormManager.h"
#include "Models.Student.h"
#include "Models.WaterRecord.h"
#include "RecordManager.h"
#include <vector>

using namespace winrt::Heyiwei2::Models;
using namespace winrt::Windows::Foundation::Collections;

class DormManager : public IDormManager
{
private:
    std::vector<Student> students;
    IObservableVector<WaterRecord> waterRecords;
    RecordManager recordManager;

public:
    DormManager();
    std::vector<Student> getAllStudents() override;
    Result addStudent(const Student& student) override;
    Result removeStudent(const winrt::hstring& id) override;
    Result updateStudentName(const winrt::hstring& id, const winrt::hstring& name) override;
    Student queryStudent(const winrt::hstring& id);
    IObservableVector<WaterRecord> queryWaterRecords();
    WaterRecord querySpecificWaterRecord(int year, int month);
    Result addWaterRecord(WaterRecord const& record);
    Result removeWaterRecord(int year, int month);
    Result updateWaterRecord(int year, int month, double usage);
};