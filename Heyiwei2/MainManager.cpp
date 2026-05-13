#include "pch.h"
#include "MainManager.h"

using namespace winrt::Heyiwei2::Models;
using namespace winrt::Windows::Foundation;

const Collections::IObservableVector<IInspectable>& MainManager::getAllDorms()
{
	return dorms;
}
