#include "pch.h"
#include "CppUnitTest.h"
#include "../Heyiwei2/StudentManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			StudentManager studentManager;
			int result = studentManager.outputInfo();
			Assert::AreEqual(10, result);
		}
	};
}
