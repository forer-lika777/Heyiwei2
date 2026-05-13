#include "pch.h"
#include "MainManager.h"

using namespace winrt::Heyiwei2::Models;
using namespace winrt::Windows::Foundation;

const Collections::IObservableVector<IInspectable>& MainManager::getAllDorms()
{
	return dorms;
}

Result MainManager::addStudent(Student const& student)
{
	return Result();
}

Result MainManager::removeStudent(const winrt::hstring& id)
{
	return Result();
}
