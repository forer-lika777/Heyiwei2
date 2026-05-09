#include "pch.h"
#include <iostream>
#include "../Heyiwei2/StudentManager.h"

TEST(studentManager_test, test1) {
	StudentManager studentManager;
	std::cout << studentManager.outputInfo();
}