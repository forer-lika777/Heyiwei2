#pragma once
#include <vector>
#include "Models.Dorm.h"

using namespace winrt::Heyiwei2::Models;
using namespace winrt::Windows::Foundation;

class MainManager
{
private:
	Collections::IObservableVector<IInspectable>& dorms;

public:
	MainManager(Collections::IObservableVector<IInspectable>& dorms) : dorms(dorms) {}
	const Collections::IObservableVector<IInspectable>& getAllDorms();
};

