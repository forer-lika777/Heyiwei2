#include "pch.h"
#include "MainManager.h"
#include "Models.Result.h"
#include "Utils.h"
#include "DataSaveService.h"

using namespace winrt::Heyiwei2::Models;
using namespace winrt::Windows::Foundation;
using namespace winrt;
using namespace winrt::Windows::Storage;

//extern void SaveData(const winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>& dorms, const std::string& filename);
//extern winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> LoadData(const std::string& filename);
MainManager::MainManager(IObservableVector /*：可观测动态数组，ui随数据改变而改变*/<IInspectable>& dorms) : dorms(dorms) {

}

// 保存功能实现
void MainManager::SaveCurrentData()
{
	// 直接把你持有的 m_dorms 喂给队友的静态方法（或实例方法）
	// 如果 SaveToFile 是静态函数，直接这样写：
	DataSaveService::SaveToFile(dorms);

	// 如果 DataSaveService 需要实例化，则写成：
	// DataSaveService service;
	// service.SaveToFile(m_dorms);
}

// 加载功能实现
void MainManager::LoadStoredData()
{
	// 1. 调用队友写的反序列化函数，拿到从 JSON 恢复出来的 WinRT 集合
	auto loadedDorms = DataSaveService::LoadFromFile();

	// 2. 【核心防错与联动】
	// 绝对不能直接写 m_dorms = loadedDorms; 因为 m_dorms 是引用，直接赋值会断开与前端 UI 的链接！
	// 必须清空原有数据，然后把新数据一个个 Append 进去，这样前端的 ListView 才会瞬间自动刷新。
	dorms.Clear();
	for (uint32_t i = 0; i < loadedDorms.Size(); ++i)
	{
		dorms.Append(loadedDorms.GetAt(i));
	}
}

winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> MainManager::getDormItems() {
	return dorms;
}

Dorm MainManager::getDorm(const hstring dormId) {
	int32_t index = findDormIndex(dormId);

	if (index == -1) return nullptr;

	return dorms.GetAt(index).as<Dorm>();
}

Result MainManager::addStudent(const hstring dormId, Student const student) {
	for (auto dorm : dorms) {
		for (auto s : dorm.as<Dorm>().Students()) {
			if (s.as<Student>().StudentId() == student.StudentId()) {
				return winrt::make<implementation::Result>(
					false,
					L"添加失败：已存在相同学号的学生"
				);
			}
		}
	}

	int32_t index = findDormIndex(dormId);

	if (index == -1) {
		return winrt::make<implementation::Result>(
			false,
			L"添加失败：宿舍不存在"
		);
	}

	auto result = Utils::validateStudent(student);
	if (!result.Success()) return result;

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	result = dormManager.addStudent(student);

	SaveCurrentData();

	return result;
}

Result MainManager::removeStudent(const hstring dormId, const hstring studentId) {
	int32_t index = findDormIndex(dormId);

	if (index == -1) {
		return winrt::make<implementation::Result>(
			false,
			L"删除失败：宿舍不存在"
		);
	}

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	auto result = dormManager.removeStudent(studentId);

	SaveCurrentData();

	return result;
}

Result MainManager::updateStudent(const hstring dormId, const hstring studentId, Student const student) {
	for (auto dorm : dorms) {
		for (auto s : dorm.as<Dorm>().Students()) {
			if (s.as<Student>().StudentId() == student.StudentId()) {
				return winrt::make<implementation::Result>(
					false,
					L"更新失败：已存在相同学号的学生"
				);
			}
		}
	}

	int32_t index = findDormIndex(dormId);

	if (index == -1) {
		return winrt::make<implementation::Result>(
			false,
			L"修改失败：宿舍不存在"
		);
	}

	auto result = Utils::validateStudent(student);
	if (!result.Success()) return result;

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	result = dormManager.updateStudent(
		studentId,
		student
	);

	SaveCurrentData();

	return result;
}

Result MainManager::addDorm(const Dorm dorm) {
	int32_t index = findDormIndex(dorm.DormId());

	if (index != -1) {
		return winrt::make<implementation::Result>(
			false,
			L"添加失败：宿舍已存在"
		);
	}

	auto result = Utils::valideDormInfo(dorm.Info());
	if (!result.Success()) return result;

	dorms.Append(dorm);
	SaveCurrentData();

	return winrt::make<implementation::Result>(
		true,
		L"添加成功"
	);
}

Result MainManager::removeDorm(const hstring dormId) {
	int32_t index = findDormIndex(dormId);

	if (index == -1) {
		return winrt::make<implementation::Result>(
			false,
			L"删除失败：宿舍不存在"
		);
	}

	dorms.RemoveAt(index);
	SaveCurrentData();

	return winrt::make<implementation::Result>(
		true,
		L"删除成功"
	);
}

Result MainManager::updateDorm(const hstring dormId, const Dorm dorm) {
	int32_t index = findDormIndex(dormId);

	if (index == -1) {
		return winrt::make<implementation::Result>(
			false,
			L"修改失败：宿舍不存在"
		);
	}

	auto result = Utils::valideDormInfo(dorm.Info());
	if (!result.Success()) return result;

	dorms.SetAt(index, dorm);
	SaveCurrentData();

	return winrt::make<implementation::Result>(
		true,
		L"修改成功"
	);
}

Result MainManager::updateDormInfo(const hstring dormId, const DormInfo info) {
	int32_t index = findDormIndex(dormId);

	if (index == -1) {
		return winrt::make<implementation::Result>(
			false,
			L"修改失败：宿舍不存在"
		);
	}

	hstring id = Utils::generateDormId(info);

	if (dormId != Utils::generateDormId(info) && findDormIndex(id) != -1) {
		return winrt::make<implementation::Result>(
			false,
			L"修改失败：已存在信息重合的宿舍"
		);
	}

	auto result = Utils::valideDormInfo(info);
	if (!result.Success()) return result;

	auto dorm = dorms.GetAt(index).as<Dorm>();

	dorm.Info(info);

	SaveCurrentData();

	return winrt::make<implementation::Result>(
		true,
		L"修改成功"
	);
}

//Result MainManager::addStudentToDorm(const hstring dormId, const hstring studentId) {
//	int32_t index = findDormIndex(dormId);
//
//	if (index == -1) {
//		return winrt::make<implementation::Result>(
//			false,
//			L"添加失败：宿舍不存在"
//		);
//	}
//
//	dormManager.setDorm(
//		dorms.GetAt(index).as<Dorm>()
//	);
//
//	auto student = winrt::make<implementation::Student>();
//
//	student.StudentId(studentId);
//
//	return dormManager.addStudent(student);
//}
//
//Result MainManager::removeStudentFromDorm(const hstring dormId, const hstring studentId) {
//	int32_t index = findDormIndex(dormId);
//
//	if (index == -1) {
//		return winrt::make<implementation::Result>(
//			false,
//			L"删除失败：宿舍不存在"
//		);
//	}
//
//	dormManager.setDorm(
//		dorms.GetAt(index).as<Dorm>()
//	);
//
//	return dormManager.removeStudent(studentId);
//}
//
//Result MainManager::updateStudentInDorm(const hstring dormId, const hstring studentId, const Student student) {
//	int32_t index = findDormIndex(dormId);
//
//	if (index == -1) {
//		return winrt::make<implementation::Result>(
//			false,
//			L"修改失败：宿舍不存在"
//		);
//	}
//
//	dormManager.setDorm(
//		dorms.GetAt(index).as<Dorm>()
//	);
//
//	return dormManager.updateStudentName(
//		studentId,
//		student.Name()
//	);
//}

Result MainManager::addWaterRecord(const hstring dormId, const WaterRecord record) {
	int32_t index = findDormIndex(dormId);

	if (index == -1) {
		return winrt::make<implementation::Result>(
			false,
			L"添加失败：宿舍不存在"
		);
	}

	auto result = Utils::validateWaterRecord(record);
	if (!result.Success()) return result;

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	SaveCurrentData();

	return dormManager.addWaterRecord(record);
}

Result MainManager::removeWaterRecord(const hstring dormId, int year, int month) {
	int32_t index = findDormIndex(dormId);

	if (index == -1) {
		return winrt::make<implementation::Result>(
			false,
			L"删除失败：宿舍不存在"
		);
	}

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	SaveCurrentData();

	return dormManager.removeWaterRecord(
		year,
		month
	);
}

Result MainManager::updateWaterRecord(const hstring dormId, int year, int month, const WaterRecord record) {
	int32_t index = findDormIndex(dormId);

	if (index == -1) {
		return winrt::make<implementation::Result>(
			false,
			L"修改失败：宿舍不存在"
		);
	}

	auto result = Utils::validateWaterRecord(record);
	if (!result.Success()) return result;

	dormManager.setDorm(
		dorms.GetAt(index).as<Dorm>()
	);

	SaveCurrentData();

	return dormManager.updateWaterRecord(
		year,
		month,
		record.Usage()
	);
}

int32_t MainManager::findDormIndex(const hstring dormId) {
	for (uint32_t i = 0; i < dorms.Size(); ++i) {
		auto dorm = dorms.GetAt(i).as<Dorm>();

		if (dorm.DormId() == dormId) {
			return static_cast<int32_t>(i);
		}
	}

	return -1;
}


