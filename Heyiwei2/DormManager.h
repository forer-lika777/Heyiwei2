#pragma once
#include "IDormManager.h"
#include "RecordManager.h"

class DormManager : public Interfaces::IDormManager
{
private:
    Dorm dorm{ nullptr };
    RecordManager recordManager;

public:
    DormManager();

	void setDorm(const Dorm dorm);

    IObservableVector<IInspectable> getAllStudents() override;

    Result addStudent(const Student& student) override;
    Result removeStudent(const winrt::hstring& id) override;
    Result updateStudent(const winrt::hstring& id, const Student& student);
    Result updateStudentName(const winrt::hstring& id, const winrt::hstring& name) override;

    int32_t queryStudent(const winrt::hstring& id);

    IObservableVector<IInspectable> getWaterRecords();

    Result addWaterRecord(WaterRecord const& record);
    Result removeWaterRecord(int year, int month);
    Result updateWaterRecord(int year, int month, double usage);

    WaterRecord querySpecificWaterRecord(int year, int month);
};