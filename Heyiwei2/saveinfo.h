#pragma once
#include <vector>
#include <string>
#include "Models.h"

void SaveData(const std::vector<Models::Dorm>& dorms, const std::string& filename);
std::vector<Models::Dorm> LoadData(const std::string& filename);