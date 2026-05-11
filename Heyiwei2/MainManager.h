#pragma once
#include <vector>
#include "Models.h"

class MainManager
{
private:
	std::vector<Models::Dorm> dorms;


public:
	const std::vector<Models::Dorm>& getAllDorms();
};

