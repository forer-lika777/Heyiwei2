#include "pch.h"
#include "CppUnitTest.h"
#include "../Heyiwei2/DormManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			DormManager dormManager;
			int result = dormManager.addNum(1, 2);
			Assert::AreEqual(3, result);
		}
	};
}
