#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include "Table.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RDBMS_Tests
{		
	TEST_CLASS(Table_Tests)
	{
	public:
		
		TEST_METHOD(test_Table_getName)
		{
			Table *table = new Table("Test Table Name");

			Assert::AreEqual<string>(table->get_Name(), "Test Table Name");
		}

	};
}