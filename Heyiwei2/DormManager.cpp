// 预处理头文件
#include "pch.h"
#include "DormManager.h"

using namespace winrt::Heyiwei2::Models;

DormManager::DormManager() : recordManager(waterRecords)
{
}

// getAllStudents: 返回所有学生列表
std::vector<Student> const& DormManager::getAllStudents() const
{
    return students;
}

// addStudent: 添加学生，若学号已存在则返回失败
Result DormManager::addStudent(const Student& student)
{
    for (const auto& s : students)
    {
        if (s.StudentId() == student.StudentId())
        {
            return Result{ false, L"添加失败：学号已存在" };
        }
    }
    students.push_back(student);
    return Result{ true, L"添加成功" };
}

// removeStudent: 根据学号删除学生，若未找到则返回失败
Result DormManager::removeStudent(const winrt::hstring& id)
{
    for (auto it = students.begin(); it != students.end(); ++it)
    {
        if (it->StudentId() == id)
        {
            students.erase(it);
            return Result{ true, L"删除成功" };
        }
    }
    return Result{ false, L"删除失败：未找到该学生" };
}

// updateStudentName: 根据学号修改学生姓名，若未找到则返回失败
Result DormManager::updateStudentName(const winrt::hstring& id, const winrt::hstring& name)
{
    for (auto& s : students)
    {
        if (s.StudentId() == id)
        {
            s.Name(name);
            return Result{ true, L"修改成功" };
        }
    }
    return Result{ false, L"修改失败：未找到该学生" };
}

// queryStudent: 根据学号查询学生，若未找到返回空对象
Student DormManager::queryStudent(const winrt::hstring& id)
{
    for (const auto& s : students)
    {
        if (s.StudentId() == id)
        {
            return s;
        }
    }
    return nullptr;
}

// queryWaterRecords: 返回宿舍所有水费记录列表
IObservableVector<WaterRecord> DormManager::queryWaterRecords()
{
    return waterRecords;
}

// querySpecificWaterRecord: 根据年月查询特定水费记录，若未找到返回空对象
WaterRecord DormManager::querySpecificWaterRecord(int year, int month)
{
    auto index = recordManager.querySpecificWaterRecord(year, month);
    if (index == -1)
    {
        return WaterRecord{ nullptr };
    }
    return waterRecords.GetAt(index);
}

// addWaterRecord: 添加水费记录，若已存在同年月记录则返回失败
Result DormManager::addWaterRecord(WaterRecord const& record)
{
    return recordManager.addWaterRecord(record);
}

// removeWaterRecord: 根据年月删除水费记录，若未找到则返回失败
Result DormManager::removeWaterRecord(int year, int month)
{
    return recordManager.removeWaterRecord(year, month);
}

// updateWaterRecord: 根据年月修改水费记录用量，若未找到则返回失败
Result DormManager::updateWaterRecord(int year, int month, double usage)
{
    return recordManager.updateWaterRecord(year, month, usage);
}