#pragma once
#include <vector>
#include "Models.Dorm.h"

using namespace winrt::Heyiwei2::Models;
using namespace winrt::Windows::Foundation;

class MainManager
{
private:
	IObservableVector<IInspectable>& dorms;

public:
	MainManager(IObservableVector<IInspectable>& dorms) : dorms(dorms) {}
	const std::vector<Dorm>& getAllDorms();
};

