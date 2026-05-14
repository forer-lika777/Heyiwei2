#include "pch.h"
#include "MainManager.h"

using namespace winrt::Heyiwei2::Models;
using namespace winrt::Windows::Foundation;

MainManager::MainManager(IObservableVector<IInspectable>& dorms) : dorms(dorms)
{

}

Result MainManager::addStudent(const hstring dormId, Student const student)
{
	return winrt::make<implementation::Result>(false, L"功能未实现");
}

Result MainManager::removeStudent(const hstring dormId, const hstring studentId)
{
	return winrt::make<implementation::Result>(false, L"功能未实现");
}

Result MainManager::updateStudent(const hstring dormId, const hstring studentId, const hstring name)
{
	return winrt::make<implementation::Result>(false, L"功能未实现");
}

Result MainManager::addDorm(const Dorm dorm)
{
	return winrt::make<implementation::Result>(false, L"功能未实现");
}

Result MainManager::removeDorm(const hstring dormId)
{
	return winrt::make<implementation::Result>(false, L"功能未实现");
}

Result MainManager::updateDorm(const hstring dormId, const Dorm dorm)
{
	return winrt::make<implementation::Result>(false, L"功能未实现");
}

Result MainManager::addStudentToDorm(const hstring dormId, const hstring studentId)
{
	return winrt::make<implementation::Result>(false, L"功能未实现");
}

Result MainManager::removeStudentFromDorm(const hstring dormId, const hstring studentId)
{
	return winrt::make<implementation::Result>(false, L"功能未实现");
}

Result MainManager::updateStudentInDorm(const hstring dormId, const hstring studentId, const Student student)
{
	return winrt::make<implementation::Result>(false, L"功能未实现");
}

Result MainManager::addWaterRecord(const hstring dormId, const WaterRecord record)
{
	return winrt::make<implementation::Result>(false, L"功能未实现");
}

Result MainManager::removeWaterRecord(const hstring dormId, int year, int month)
{
	return winrt::make<implementation::Result>(false, L"功能未实现");
}

Result MainManager::updateWaterRecord(const hstring dormId, int year, int month, const WaterRecord record)
{
	return winrt::make<implementation::Result>(false, L"功能未实现");
}

int32_t MainManager::findDormIndex(const hstring dormId)
{
	return -1;
}


