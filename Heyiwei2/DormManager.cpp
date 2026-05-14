// 预处理头文件
#include "pch.h"
#include "DormManager.h"

using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Heyiwei2::Models;

DormManager::DormManager()
{
}

void DormManager::setDorm(const Dorm dorm)
{
    this->dorm = dorm;
}

IObservableVector<IInspectable> DormManager::getAllStudents()
{
    return dorm.Students();
}

// addStudent: 添加学生，若学号已存在则返回失败
Result DormManager::addStudent(const Student& student)
{
    int32_t index = queryStudent(student.StudentId());
    if (index != -1)
    {
        return winrt::make<implementation::Result>(false, L"添加失败：学号已存在");
    }
    dorm.Students().Append(student);
    return winrt::make<implementation::Result>(true, L"添加成功");
}

// removeStudent: 根据学号删除学生，若未找到则返回失败
Result DormManager::removeStudent(const winrt::hstring& id)
{
    int32_t index = queryStudent(id);
	if (index != -1)
	{
		dorm.Students().RemoveAt(index);
		return winrt::make<implementation::Result>(true, L"删除成功");
	}
    return winrt::make<implementation::Result>(false, L"删除失败：未找到该学生" );
}

// updateStudentName: 根据学号修改学生姓名，若未找到则返回失败
Result DormManager::updateStudentName(const winrt::hstring& id, const winrt::hstring& name)
{
	int32_t index = queryStudent(id);
	if (index != -1)
	{
		auto s = dorm.Students().GetAt(index).as<Student>();
		s.Name(name);
		return winrt::make<implementation::Result>(true, L"修改成功" );
	}
    return winrt::make<implementation::Result>(false, L"修改失败：未找到该学生" );
}

// queryStudent: 根据学号查询学生，若未找到返回空对象
int32_t DormManager::queryStudent(const winrt::hstring& id)
{
    auto students = dorm.Students();
    for (uint32_t i = 0; i < students.Size(); i++)
    {
        auto s = students.GetAt(i).as<Student>();
        if (s.StudentId() == id)
        {
            return static_cast<int32_t>(i);
        }
    }
    return -1;
}

// queryWaterRecords: 返回宿舍所有水费记录列表
IObservableVector<IInspectable> DormManager::getWaterRecords()
{
    return dorm.Records();
}

// querySpecificWaterRecord: 根据年月查询特定水费记录，若未找到返回空对象
WaterRecord DormManager::querySpecificWaterRecord(int year, int month)
{
    auto index = recordManager.querySpecificWaterRecord(year, month);
    if (index == -1)
    {
        return WaterRecord{ nullptr };
    }
    return dorm.Records().GetAt(index).as<WaterRecord>();
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