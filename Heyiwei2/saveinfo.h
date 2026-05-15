#pragma once
#include <vector>
#include <string>
#include "Models.Result.h"
#include "Models.Dorm.h"

void SaveData(const winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable>& dorms, const std::string& filename);
winrt::Windows::Foundation::Collections::IObservableVector<winrt::Windows::Foundation::IInspectable> LoadData(const std::string& filename);