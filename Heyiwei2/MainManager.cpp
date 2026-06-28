#include "pch.h"
#include "MainManager.h"
#include "DataSaveService.h"
#include "Utils.h"

#include "Models.Result.h"
#include "Models.Dorm.h"

using namespace winrt::Heyiwei2::Models;
using namespace winrt::Windows::Foundation;
using namespace winrt;
using namespace winrt::Windows::Storage;

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

/// <summary>
/// 触发保存数据
/// </summary>
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

/// <summary>
/// 获取持有的 dorms 列表对象
/// </summary>
/// <returns>宿舍列表对象</returns>
winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> MainManager::getDormItems() {
	return dorms;
}

/// <summary>
/// 依据宿舍id获取宿舍对象
/// </summary>
/// <param name="dormId">宿舍id</param>
/// <returns>目标宿舍对象</returns>
Dorm MainManager::getDorm(hstring const& dormId) {
	int32_t index = findDormIndex(dormId);

	if (index == -1) return nullptr;

	return dorms.GetAt(index).as<Dorm>();
}

/// <summary>
/// 添加学生至目标宿舍
/// </summary>
/// <param name="dormId">宿舍id</param>
/// <param name="student">学生对象</param>
/// <returns>操作结果</returns>
Result MainManager::addStudent(hstring const& dormId, Student const& student) {
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

	auto dorm = dorms.GetAt(index).as<Dorm>();
	dormManager.setDorm(dorm);

	result = dormManager.addStudent(student);

	dorm.RefreshStudentsCount();
	dorm.RefreshStatus();
	SaveCurrentData();

	return result;
}

/// <summary>
/// 移除学生
/// </summary>
/// <param name="dormId">宿舍id</param>
/// <param name="studentId">要移除的学生id</param>
/// <returns>操作结果</returns>
Result MainManager::removeStudent(hstring const& dormId, hstring const& studentId) {
	int32_t index = findDormIndex(dormId);

	if (index == -1) {
		return winrt::make<implementation::Result>(
			false,
			L"删除失败：宿舍不存在"
		);
	}

	auto dorm = dorms.GetAt(index).as<Dorm>();
	dormManager.setDorm(dorm);

	auto result = dormManager.removeStudent(studentId);

	dorm.RefreshStudentsCount();
	dorm.RefreshStatus();
	SaveCurrentData();

	return result;
}

/// <summary>
/// 更新学生
/// </summary>
/// <param name="dormId">宿舍id</param>
/// <param name="studentId">学生id</param>
/// <param name="student">要更新的学生</param>
/// <returns>操作结果</returns>
Result MainManager::updateStudent(hstring const& dormId, hstring const& studentId, Student const& student) {
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

	auto dorm = dorms.GetAt(index).as<Dorm>();

	dormManager.setDorm(dorm);

	result = dormManager.updateStudent(
		studentId,
		student
	);
	
	SaveCurrentData();

	return result;
}

/// <summary>
/// 添加宿舍
/// </summary>
/// <param name="dorm">要添加的宿舍</param>
/// <returns>操作结果</returns>
Result MainManager::addDorm(Dorm const& dorm) {
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

/// <summary>
/// 移除宿舍
/// </summary>
/// <param name="dormId">要移除的宿舍id</param>
/// <returns>操作结果</returns>
Result MainManager::removeDorm(hstring const& dormId) {
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

/// <summary>
/// 更新宿舍（将替换所有学生和水费记录）
/// </summary>
/// <param name="dormId">宿舍id</param>
/// <param name="dorm">要替换的宿舍对象</param>
/// <returns>操作结果</returns>
Result MainManager::updateDorm(hstring const& dormId, Dorm const& dorm) {
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

/// <summary>
/// 更新宿舍信息
/// </summary>
/// <param name="dormId">宿舍id</param>
/// <param name="info">要更新的宿舍信息</param>
/// <returns>操作结果</returns>
Result MainManager::updateDormInfo(hstring const& dormId, DormInfo const& info) {
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

	//dorm.RefreshStatus();
	SaveCurrentData();

	return winrt::make<implementation::Result>(
		true,
		L"修改成功"
	);
}

//Result MainManager::addStudentToDorm(hstring const& dormId, hstring const& studentId) {
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
//Result MainManager::removeStudentFromDorm(hstring const& dormId, hstring const& studentId) {
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
//Result MainManager::updateStudentInDorm(hstring const& dormId, hstring const& studentId, const Student student) {
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

/// <summary>
/// 添加用水记录
/// </summary>
/// <param name="dormId">宿舍id</param>
/// <param name="record">要添加的水费记录</param>
/// <returns>操作结果</returns>
Result MainManager::addWaterRecord(hstring const& dormId, WaterRecord const& record) {
	int32_t index = findDormIndex(dormId);

	if (index == -1) {
		return winrt::make<implementation::Result>(
			false,
			L"添加失败：宿舍不存在"
		);
	}

	auto result = Utils::validateWaterRecord(record);
	if (!result.Success()) return result;

	auto dorm = dorms.GetAt(index).as<Dorm>();
	dormManager.setDorm(dorm);

	result = dormManager.addWaterRecord(record);

	if (!result.Success()) return result;

	Utils::sortWaterRecords(dorm.Records());

	dorm.RefreshStatus();
	dorm.RefreshRecordsCount();
	SaveCurrentData();

	return result;
}

/// <summary>
/// 移除用水记录
/// </summary>
/// <param name="dormId">宿舍id</param>
/// <param name="year">年份</param>
/// <param name="month">月份</param>
/// <returns>操作结果</returns>
Result MainManager::removeWaterRecord(hstring const& dormId, int year, int month) {
	int32_t index = findDormIndex(dormId);

	if (index == -1) {
		return winrt::make<implementation::Result>(
			false,
			L"删除失败：宿舍不存在"
		);
	}

	auto dorm = dorms.GetAt(index).as<Dorm>();
	dormManager.setDorm(dorm);

	auto result = dormManager.removeWaterRecord(
		year,
		month
	);

	if (!result.Success()) return result;

	dorm.RefreshStatus();
	dorm.RefreshRecordsCount();
	SaveCurrentData();

	return result;
}

/// <summary>
/// 更新水费记录
/// </summary>
/// <param name="dormId">宿舍id</param>
/// <param name="year">年份</param>
/// <param name="month">月份</param>
/// <param name="record">要替换的水费信息</param>
/// <returns>操作结果</returns>
Result MainManager::updateWaterRecord(hstring const& dormId, int year, int month, WaterRecord const& record) {
	int32_t index = findDormIndex(dormId);

	if (index == -1) {
		return winrt::make<implementation::Result>(
			false,
			L"修改失败：宿舍不存在"
		);
	}

	auto result = Utils::validateWaterRecord(record);
	if (!result.Success()) return result;

	auto dorm = dorms.GetAt(index).as<Dorm>();
	dormManager.setDorm(dorm);

	result = dormManager.updateWaterRecord(
		year,
		month,
		record.Usage()
	);

	if (!result.Success()) return result;

	dorm.RefreshStatus();
	SaveCurrentData();

	return result;
}

/// <summary>
/// 查找宿舍索引
/// </summary>
/// <param name="dormId">宿舍id</param>
/// <returns>索引值</returns>
int32_t MainManager::findDormIndex(hstring const& dormId) {
	for (uint32_t i = 0; i < dorms.Size(); ++i) {
		auto dorm = dorms.GetAt(i).as<Dorm>();

		if (dorm.DormId() == dormId) {
			return static_cast<int32_t>(i);
		}
	}

	return -1;
}