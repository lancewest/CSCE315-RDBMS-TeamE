#include "stdafx.h"
#include "CppUnitTest.h"

#include "DB_Engine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace RDBMS_Tests
{
	TEST_CLASS(DB_Engine_Tests)
	{
	public:
		
		/*TEST_METHOD(test_DBEngine_Create_Table)
		{
			DB_Engine *engine = new DB_Engine();

			engine->create_Table("Clients");

			Assert::IsTrue(engine->get_Tables().size() == 1);
			Assert::IsTrue(engine->get_Tables()[0].get_Name() == "Clients");
		}

		TEST_METHOD(test_DBEngine_Show)
		{
			DB_Engine *engine = new DB_Engine();

			fill_Engine(engine);

			engine->show( get_Table(engine, "Clients") ); //Ensures no unknown exceptions in Show()
		}

		bool attribute_Value_Is_Robert_Smith(Attribute a)
		{
			return a.get_String_Value() == "Robert Smith";
		}

		TEST_METHOD(test_DBEngine_Update)
		{
			DB_Engine *engine = new DB_Engine();

			fill_Engine(engine);

			Attribute *new_attribute = new Attribute("Robert Smith", false, "Client Name", 1);

			bool  (*funct)(Attribute a) = attribute_Value_Is_Robert_Smith;

			engine->update( get_Table(engine, "Clients"), "Client Id",  *new_attribute, funct);
		}

		TEST_METHOD(test_DBEngine_Insert)
		{
			DB_Engine *engine = new DB_Engine();

			fill_Engine(engine);

			Attribute *client_id = new Attribute(123, true, "Client Id");
			Attribute *client_name = new Attribute("Lance West", false, "Client Name", 1);
			vector<Attribute> tuple_attributes;
			tuple_attributes.push_back(*client_id);
			tuple_attributes.push_back(*client_name);
			Tuple *tuple = new Tuple(tuple_attributes);


			Assert::IsTrue( get_Table(engine, "Clients").get_Tuples().size() == 2 );

			engine->insert( get_Table(engine, "Clients"), *tuple );

			Assert::IsTrue( get_Table(engine, "Clients").get_Tuples().size() == 3 );
			Assert::IsTrue( get_Table(engine, "Clients").get_Tuples()[2] == *tuple );
		}

		TEST_METHOD(test_DBEngine_Erase_Table)
		{
			DB_Engine *engine = new DB_Engine();

			fill_Engine(engine);

			Assert::IsTrue( engine->get_Tables().size() == 2 );

			engine->erase( get_Table(engine, "Clients") );

			Assert::IsTrue( engine->get_Tables().size() == 1 );
		}

		TEST_METHOD(test_DBEngine_Erase_Tuple)
		{
			DB_Engine *engine = new DB_Engine();

			fill_Engine(engine);

			Assert::IsTrue( engine->get_Tables()[0].get_Tuples().size() == 2 );

			engine->erase( get_Table(engine, "Clients"), engine->get_Tables()[0].get_Tuples()[0] );

			Assert::IsTrue( engine->get_Tables()[0].get_Tuples().size() == 1 );
		}

		TEST_METHOD(test_DBEngine_Select)
		{
			DB_Engine *engine = new DB_Engine();

			fill_Engine(engine);

			Assert::IsTrue( engine->get_Tables()[0].get_Tuples().size() == 2 );

			engine->erase( get_Table(engine, "Clients"), engine->get_Tables()[0].get_Tuples()[0] );

			Assert::IsTrue( engine->get_Tables()[0].get_Tuples().size() == 1 );
		}

		TEST_METHOD(test_DBEngine_Project)
		{
			DB_Engine *engine = new DB_Engine();

			fill_Engine(engine);

			Attribute *client_name = new Attribute("test name", false, "Client Name", 1);
			vector<Attribute> tuple1_attributes;
			tuple1_attributes.push_back(*client_name);
			Tuple *tuple = new Tuple(tuple1_attributes);

			Table test = engine->project( get_Table(engine, "Clients"), *tuple);

			Assert::IsTrue(test.get_Tuples().size() == 2);
			Assert::IsTrue(test.get_Tuples()[0].get_Attributes().size() == 1);
			Assert::IsTrue(test.get_Tuples()[0].get_Attributes()[0].get_String_Value() == "Bob Smith");
			Assert::IsTrue(test.get_Tuples()[0].get_Attributes()[0].get_String_Value() == "Joe Shmoe");
		}

		void fill_Engine(DB_Engine *engine)
		{
			Attribute *client_id = new Attribute(123, true, "Client Id");
			Attribute *client_name = new Attribute("Bob Smith", false, "Client Name", 1);
			vector<Attribute> tuple1_attributes;
			tuple1_attributes.push_back(*client_id);
			tuple1_attributes.push_back(*client_name);
			Tuple *tuple1 = new Tuple(tuple1_attributes);

			Attribute *client_id2 = new Attribute(321, true, "Client Id");
			Attribute *client_name2 = new Attribute("Joe Shmoe", false, "Client Name", 1);
			vector<Attribute> tuple2_attributes;
			tuple2_attributes.push_back(*client_id2);
			tuple2_attributes.push_back(*client_name2);
			Tuple *tuple2 = new Tuple(tuple2_attributes);

			Attribute *client_ida = new Attribute(123, true, "Client Id");
			Attribute *account_id = new Attribute(1, false, "Account Id");
			vector<Attribute> tuple1a_attributes;
			tuple1a_attributes.push_back(*client_ida);
			tuple1a_attributes.push_back(*account_id);
			Tuple *tuple1_accounts = new Tuple(tuple1a_attributes);

			Attribute *client_ida2 = new Attribute(321, true, "Client Id");
			Attribute *account_id2 = new Attribute(2, false, "Accoutnt Id");
			vector<Attribute> tuple2a_attributes;
			tuple2a_attributes.push_back(*client_ida2);
			tuple2a_attributes.push_back(*account_id2);
			Tuple *tuple2_accounts = new Tuple(tuple2a_attributes);

			Attribute *client_ida3 = new Attribute(321, true, "Client Id");
			Attribute *account_id3 = new Attribute(3, false, "Account Id");
			vector<Attribute> tuple3a_attributes;
			tuple3a_attributes.push_back(*client_ida3);
			tuple3a_attributes.push_back(*account_id3);
			Tuple *tuple3_accounts = new Tuple(tuple3a_attributes);

			engine->create_Table("Clients");
			engine->create_Table("Accounts");

			engine->insert(get_Table(engine, "Clients"), *tuple1);
			engine->insert(get_Table(engine, "Clients"), *tuple2);
			engine->insert(get_Table(engine, "Accounts"), *tuple1_accounts);
			engine->insert(get_Table(engine, "Accounts"), *tuple2_accounts);
			engine->insert(get_Table(engine, "Accounts"), *tuple3_accounts);
		}

		Table get_Table(DB_Engine *engine, string table_Name)
		{
			for(Table i : engine->get_Tables())
			{
				if(i.get_Name() == table_Name)
				{
					return i;
				}
			}

			return NULL;
		}*/

		

	};
}