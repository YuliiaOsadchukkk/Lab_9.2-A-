#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_9.2(A)/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Lab92AUT
{
	TEST_CLASS(Lab92AUT)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int N = 0;
			int t = 0;
			Sort(0, N);
			Assert::AreEqual(t, 0);
		}
	};
}
