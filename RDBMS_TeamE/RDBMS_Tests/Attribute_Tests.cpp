#include "stdafx.h"
#include "CppUnitTest.h"

#include "table.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RDBMS_Tests
{
  TEST_CLASS(Attribute_Tests)
  {
  public:
		
    TEST_METHOD(test_Attribute_Equals)
    {
      Attribute *one = new Attribute(123, true, "Client Id");
      Attribute *two = new Attribute("Bob", false, "Client Name", 1);
      Attribute *three = new Attribute("Bob", false, "Client Name", 1);
      Attribute *four = new Attribute("123", true, "Client Id", -1);
			
      Assert::IsTrue(*two == *three);
      Assert::IsFalse(*one == *two);
      Assert::IsFalse(*one == *four);
      Assert::IsFalse(*four == *one);
    }

    TEST_METHOD(test_Attribute_Not_Equals)
    {
      Attribute *one = new Attribute(123, true, "Client Id");
      Attribute *two = new Attribute("Bob", false, "Client Name", 1);
      Attribute *three = new Attribute("Bob", false, "Client Name", 1);
      Attribute *four = new Attribute("123", true, "Client Id", -1);
			
      Assert::IsFalse(*two != *three);
      Assert::IsTrue(*one != *two);
      Assert::IsTrue(*one != *four);
      Assert::IsTrue(*four != *one);
    }

    TEST_METHOD(test_Attribute_Is_Compatible)
   {
      Attribute *int_one = new Attribute(123, true, "Client Id");
      Attribute *int_two = new Attribute(99, true, "Client Id");
      Attribute *string_one = new Attribute("Bob", true, "Client Name", 1);
      Attribute *string_two = new Attribute("Jo", false, "Client Name", 1);
      Attribute *string_three = new Attribute("Tod", false, "Client Name", 10);

      Assert::IsFalse(int_one->is_Compatible(*string_one));
      Assert::IsFalse(string_one->is_Compatible(*string_three));
      Assert::IsTrue(int_one->is_Compatible(*int_two));
      Assert::IsTrue(string_one->is_Compatible(*string_two));
    }

    TEST_METHOD(test_Attribute_Name)
    {
      Attribute *test = new Attribute(123, true, "Client Id");
      Assert::IsTrue(test->get_Name() == "Client Id");

      test->set_Name("New Name");
      Assert::IsTrue(test->get_Name() == "New Name");
    }

    TEST_METHOD(test_Attribute_Constructors)
    {
      Attribute *int_test = new Attribute(123, true, "Client Id");
      Attribute *string_test = new Attribute("Bob", false, "Client Name", 1);

      Assert::IsTrue(int_test->get_Name() == "Client Id");
      Assert::IsTrue(int_test->is_Primary() == true);
      Assert::IsTrue(string_test->get_Name() == "Client Name");
      Assert::IsTrue(string_test->is_Primary() == false);
    }

  };
}

