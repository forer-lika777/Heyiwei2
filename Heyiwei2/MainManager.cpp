#include "pch.h"
#include "MainManager.h"
#include "Models.Result.h"

using namespace winrt::Heyiwei2::Models;
using namespace winrt::Windows::Foundation;

MainManager::MainManager(IObservableVector<IInspectable>& dorms) : dorms(dorms)
{

}

winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> MainManager::getDormItems()
{
	return dorms;
}

Result MainManager::addStudent(const hstring dormId, Student const student)
{
	int32_t index = findDormIndex(dormId);

	if (index == -1)
	{
		return winrt::make<implementation::Result>(
			false,
			L"添加失败：宿舍不存在"
		);
	}

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	return dormManager.addStudent(student);
}

Result MainManager::removeStudent(const hstring dormId, const hstring studentId)
{
	int32_t index = findDormIndex(dormId);

	if (index == -1)
	{
		return winrt::make<implementation::Result>(
			false,
			L"删除失败：宿舍不存在"
		);
	}

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	return dormManager.removeStudent(studentId);
}

Result MainManager::updateStudent(const hstring dormId, const hstring studentId, const hstring name)
{
	int32_t index = findDormIndex(dormId);

	if (index == -1)
	{
		return winrt::make<implementation::Result>(
			false,
			L"修改失败：宿舍不存在"
		);
	}

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	return dormManager.updateStudentName(
		studentId,
		name
	);
}

Result MainManager::addDorm(const Dorm dorm)
{
	int32_t index = findDormIndex(dorm.DormId());

	if (index != -1)
	{
		return winrt::make<implementation::Result>(
			false,
			L"添加失败：宿舍已存在"
		);
	}

	dorms.Append(dorm);

	return winrt::make<implementation::Result>(
		true,
		L"添加成功"
	);
}

Result MainManager::removeDorm(const hstring dormId)
{
	int32_t index = findDormIndex(dormId);

	if (index == -1)
	{
		return winrt::make<implementation::Result>(
			false,
			L"删除失败：宿舍不存在"
		);
	}

	dorms.RemoveAt(index);

	return winrt::make<implementation::Result>(
		true,
		L"删除成功"
	);
}

Result MainManager::updateDorm(const hstring dormId, const Dorm dorm)
{
	int32_t index = findDormIndex(dormId);

	if (index == -1)
	{
		return winrt::make<implementation::Result>(
			false,
			L"修改失败：宿舍不存在"
		);
	}

	dorms.SetAt(index, dorm);

	return winrt::make<implementation::Result>(
		true,
		L"修改成功"
	);
}

Result MainManager::addStudentToDorm(const hstring dormId, const hstring studentId)
{
	int32_t index = findDormIndex(dormId);

	if (index == -1)
	{
		return winrt::make<implementation::Result>(
			false,
			L"添加失败：宿舍不存在"
		);
	}

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	auto student = winrt::make<implementation::Student>();

	student.StudentId(studentId);

	return dormManager.addStudent(student);
}

Result MainManager::removeStudentFromDorm(const hstring dormId, const hstring studentId)
{
	int32_t index = findDormIndex(dormId);

	if (index == -1)
	{
		return winrt::make<implementation::Result>(
			false,
			L"删除失败：宿舍不存在"
		);
	}

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	return dormManager.removeStudent(studentId);
}

Result MainManager::updateStudentInDorm(const hstring dormId, const hstring studentId, const Student student)
{
	int32_t index = findDormIndex(dormId);

	if (index == -1)
	{
		return winrt::make<implementation::Result>(
			false,
			L"修改失败：宿舍不存在"
		);
	}

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	return dormManager.updateStudentName(
		studentId,
		student.Name()
	);
}

Result MainManager::addWaterRecord(const hstring dormId, const WaterRecord record)
{
	int32_t index = findDormIndex(dormId);

	if (index == -1)
	{
		return winrt::make<implementation::Result>(
			false,
			L"添加失败：宿舍不存在"
		);
	}

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	return dormManager.addWaterRecord(record);
}

Result MainManager::removeWaterRecord(const hstring dormId, int year, int month)
{
	int32_t index = findDormIndex(dormId);

	if (index == -1)
	{
		return winrt::make<implementation::Result>(
			false,
			L"删除失败：宿舍不存在"
		);
	}

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	return dormManager.removeWaterRecord(
		year,
		month
	);
}

Result MainManager::updateWaterRecord(const hstring dormId, int year, int month, const WaterRecord record)
{
	int32_t index = findDormIndex(dormId);

	if (index == -1)
	{
		return winrt::make<implementation::Result>(
			false,
			L"修改失败：宿舍不存在"
		);
	}

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	return dormManager.updateWaterRecord(
		year,
		month,
		record.Usage()
	);
}

int32_t MainManager::findDormIndex(const hstring dormId)
{
	for (uint32_t i = 0; i < dorms.Size(); ++i)
	{
		auto dorm = dorms.GetAt(i).as<Dorm>();

		if (dorm.DormId() == dormId)
		{
			return static_cast<int32_t>(i);
		}
	}

	return -1;
}


