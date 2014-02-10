#include "stdafx.h"
#include "CppUnitTest.h"

#include "Table.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RDBMS_Tests
{
	TEST_CLASS(Tuple_Tests)
	{
	public:
		
		TEST_METHOD(test_Tuple_Constructors)
		{
			Attribute *client_id = new Attribute(123, true, "Client Id");
			Attribute *client_name = new Attribute("Bob Smith", false, "Client Name", 1);
			vector<Attribute> tuple1_attributes;
			tuple1_attributes.push_back(*client_id);
			tuple1_attributes.push_back(*client_name);
			Tuple *tuple = new Tuple(tuple1_attributes);

			Assert::IsTrue(tuple->get_Size() == 2);
			Assert::IsTrue(tuple->get_Attributes()[0] == *client_id);
		}

		TEST_METHOD(test_Tuple_Equals)
		{
			Attribute *client_id = new Attribute(123, true, "Client Id");
			Attribute *client_name = new Attribute("Bob Smith", false, "Client Name", 1);
			vector<Attribute> tuple_attributes;
			tuple_attributes.push_back(*client_id);
			tuple_attributes.push_back(*client_name);
			Tuple *tuple = new Tuple(tuple_attributes);

			Attribute *client_id_clone = new Attribute(123, true, "Client Id");
			Attribute *client_name_clone = new Attribute("Bob Smith", false, "Client Name", 1);
			vector<Attribute> tuple1_clone_attributes;
			tuple1_clone_attributes.push_back(*client_id);
			tuple1_clone_attributes.push_back(*client_name);
			Tuple *tuple_clone = new Tuple(tuple1_clone_attributes);

			client_id = new Attribute(1, true, "Client Id");
			client_name = new Attribute("Craig", false, "Client Name", 1);
			tuple_attributes.push_back(*client_id);
			tuple_attributes.push_back(*client_name);
			Tuple *value = new Tuple(tuple_attributes);

			client_id = new Attribute(321, true, "Supplier Id");
			client_name = new Attribute("Joe Shmoe", false, "Supplier Name", 1);
			tuple_attributes.push_back(*client_id);
			tuple_attributes.push_back(*client_name);
			Tuple *name = new Tuple(tuple_attributes);

			client_id = new Attribute(321, false, "Client Id");
			client_name = new Attribute("Joe Shmoe", true, "Client Name", 1);
			tuple_attributes.push_back(*client_id);
			tuple_attributes.push_back(*client_name);
			Tuple *primary = new Tuple(tuple_attributes);

			client_id = new Attribute(123, true, "Client Id");
			client_name = new Attribute("Bob Smith", false, "Client Name", 10);
			tuple_attributes.push_back(*client_id);
			tuple_attributes.push_back(*client_name);
			Tuple *length = new Tuple(tuple_attributes);

			Assert::IsTrue(*tuple == *tuple_clone);
			Assert::IsFalse(*tuple == *name);
			Assert::IsFalse(*tuple == *value);
			Assert::IsFalse(*tuple == *primary);
			Assert::IsFalse(*tuple == *length);
		}

		TEST_METHOD(test_Tuple_Not_Equals)
		{
			Attribute *client_id = new Attribute(123, true, "Client Id");
			Attribute *client_name = new Attribute("Bob Smith", false, "Client Name", 1);
			vector<Attribute> tuple_attributes;
			tuple_attributes.push_back(*client_id);
			tuple_attributes.push_back(*client_name);
			Tuple *tuple = new Tuple(tuple_attributes);

			Attribute *client_id_clone = new Attribute(123, true, "Client Id");
			Attribute *client_name_clone = new Attribute("Bob Smith", false, "Client Name", 1);
			vector<Attribute> tuple1_clone_attributes;
			tuple1_clone_attributes.push_back(*client_id);
			tuple1_clone_attributes.push_back(*client_name);
			Tuple *tuple_clone = new Tuple(tuple1_clone_attributes);

			client_id = new Attribute(1, true, "Client Id");
			client_name = new Attribute("Craig", false, "Client Name", 1);
			tuple_attributes.push_back(*client_id);
			tuple_attributes.push_back(*client_name);
			Tuple *value = new Tuple(tuple_attributes);

			client_id = new Attribute(321, true, "Supplier Id");
			client_name = new Attribute("Joe Shmoe", false, "Supplier Name", 1);
			tuple_attributes.push_back(*client_id);
			tuple_attributes.push_back(*client_name);
			Tuple *name = new Tuple(tuple_attributes);

			client_id = new Attribute(321, false, "Client Id");
			client_name = new Attribute("Joe Shmoe", true, "Client Name", 1);
			tuple_attributes.push_back(*client_id);
			tuple_attributes.push_back(*client_name);
			Tuple *primary = new Tuple(tuple_attributes);

			client_id = new Attribute(123, true, "Client Id");
			client_name = new Attribute("Bob Smith", false, "Client Name", 10);
			tuple_attributes.push_back(*client_id);
			tuple_attributes.push_back(*client_name);
			Tuple *length = new Tuple(tuple_attributes);

			Assert::IsFalse(*tuple != *tuple_clone);
			Assert::IsTrue(*tuple != *name);
			Assert::IsTrue(*tuple != *value);
			Assert::IsTrue(*tuple != *primary);
			Assert::IsTrue(*tuple != *length);
		}

		TEST_METHOD(test_Tuple_Addition)
		{
			Attribute *client_id = new Attribute(123, true, "Client Id");
			Attribute *client_name = new Attribute("Bob Smith", false, "Client Name", 1);
			vector<Attribute> tuple_attributes;
			tuple_attributes.push_back(*client_id);
			tuple_attributes.push_back(*client_name);
			Tuple *bank_tuple = new Tuple(tuple_attributes);

			Attribute *supplier_id = new Attribute(42, true, "Supplier Id");
			Attribute *fruit = new Attribute("Bannana", false, "Fruit", 1);
			vector<Attribute> tuple_attributes_fruit;
			tuple_attributes_fruit.push_back(*supplier_id);
			tuple_attributes_fruit.push_back(*fruit);
			Tuple *fruit_tuple = new Tuple(tuple_attributes_fruit);

			Tuple addition = *bank_tuple + *fruit_tuple;

			Assert::IsTrue(addition.get_Size() == 4);
			Assert::IsTrue(addition.get_Attributes()[0].get_Name() == "Client Id");
			Assert::IsTrue(addition.get_Attributes()[1].get_Name() == "Client Name");
			Assert::IsTrue(addition.get_Attributes()[2].get_Name() == "Supplier Id");
			Assert::IsTrue(addition.get_Attributes()[3].get_Name() == "Fruit");
		}

		TEST_METHOD(test_Tuple_Replace_Attribute)
		{
			Attribute *client_id = new Attribute(123, true, "Client Id");
			Attribute *client_name = new Attribute("Bob Smith", false, "Client Name", 1);
			vector<Attribute> tuple_attributes;
			tuple_attributes.push_back(*client_id);
			tuple_attributes.push_back(*client_name);
			Tuple *tuple = new Tuple(tuple_attributes);

			Attribute *client_initials = new Attribute("BS", true, "Client Initials", 10);

			tuple->replace_Attribute("Client Name", *client_initials);

			Assert::IsTrue(tuple->get_Size() == 2);
			Assert::IsTrue(tuple->get_Attributes()[1].get_Name() == "Client Initials");
			Assert::IsTrue(tuple->get_Attributes()[1].is_Primary() == true);
		}

	};
}