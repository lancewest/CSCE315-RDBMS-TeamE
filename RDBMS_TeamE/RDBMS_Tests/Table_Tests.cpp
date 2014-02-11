#include "stdafx.h"
#include "CppUnitTest.h"

#include <string>
#include "Table.cpp"
#include "Attribute.cpp"
#include "Tuple.cpp"

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

    TEST_METHOD(test_Table_Insert)
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

      Table *table = new Table("Clients");

      table->insert(*tuple1);
      table->insert(*tuple2);

      Assert::AreEqual<int>(table->get_Tuples().size(), 2);
      Assert::IsTrue(table->get_Tuples()[0] == *tuple1);
      Assert::IsTrue(table->get_Tuples()[1] == *tuple2);
    }

    TEST_METHOD(test_Table_Insert_Show)
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

      Table *table = new Table("Clients");

      table->insert(*tuple1);
      table->insert(*tuple2);

      table->show(); //Test for now Exceptions thrown here
    }

    TEST_METHOD(test_Table_Vector_Constructor)
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

      vector<Tuple> tuples;
      tuples.push_back(*tuple1);
      tuples.push_back(*tuple2);

      Table *table = new Table("Clients", tuples);

      Assert::AreEqual<int>(table->get_Tuples().size(), 2);
      Assert::IsTrue(table->get_Tuples()[0] == *tuple1);
      Assert::IsTrue(table->get_Tuples()[1] == *tuple2);
    }

    TEST_METHOD(test_Table_is_Union_Compatible_True)
    {
      Table clients = get_Clients_Table();
      Table accounts = get_Accounts_Table();

      Assert::IsTrue(clients.is_Union_Compatible(clients));
    }

    TEST_METHOD(test_Table_is_Union_Compatible_False)
    {
      Table clients = get_Clients_Table();
      Table fruits = get_Fruit_Table();

      Assert::IsFalse(clients.is_Union_Compatible(fruits));
    }

    TEST_METHOD(test_Table_Remove)
    {
      Table clients = get_Clients_Table();

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

      vector<Tuple> tuples;
      tuples.push_back(*tuple1);
      tuples.push_back(*tuple2);

      Table *table = new Table("Clients", tuples);

      table->remove(*tuple1);

      Assert::IsTrue(table->get_Tuples().size() == 1);
    }

    TEST_METHOD(test_Table_Addition)
    {
      Table clients = get_Clients_Table();
      Table clients2 = get_Clients2_Table();

      Table addition = clients + clients2;

      Assert::IsTrue(addition.get_Tuples().size() == 4);
      Assert::IsTrue(addition.get_Tuples()[2] == clients2.get_Tuples()[0]);
    }

    TEST_METHOD(test_Table_Subtraction)
    {
      Table clients = get_Clients_Table();
      Table accounts = get_Accounts_Table();

      Table subtraction = accounts - clients;

      Assert::IsTrue(subtraction.get_Tuples().size() == 3); //Need to talk about what subtraction should do
    }

    TEST_METHOD(test_Table_Multiply)
    {
      Table clients = get_Clients_Table();
      Table accounts = get_Accounts_Table();

      Table multiplication = accounts * clients;

      Assert::IsTrue(multiplication.get_Tuples().size() == 6);
      Assert::IsTrue(multiplication.get_Tuples()[0].get_Attributes()[0].get_Name() == "Client Id");
    }

    TEST_METHOD(test_Table_get_Column)
    {
      Table clients = get_Clients_Table();

      vector<Attribute> columns = clients.get_Column("Client Name");

      Assert::IsTrue(columns.size() == 2);
      Assert::IsTrue(columns[0].is_Primary() == false);
    }

    Table get_Clients_Table()
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

      vector<Tuple> tuples;
      tuples.push_back(*tuple1);
      tuples.push_back(*tuple2);

      Table *table = new Table("Clients", tuples);

      return *table;
    }

	Table get_Clients2_Table()
    {
      Attribute *client_id = new Attribute(72, true, "Client Id");
      Attribute *client_name = new Attribute("Lance West", false, "Client Name", 1);
      vector<Attribute> tuple1_attributes;
      tuple1_attributes.push_back(*client_id);
      tuple1_attributes.push_back(*client_name);
      Tuple *tuple1 = new Tuple(tuple1_attributes);

      Attribute *client_id2 = new Attribute(73, true, "Client Id");
      Attribute *client_name2 = new Attribute("Iron Man", false, "Client Name", 1);
      vector<Attribute> tuple2_attributes;
      tuple2_attributes.push_back(*client_id2);
      tuple2_attributes.push_back(*client_name2);
      Tuple *tuple2 = new Tuple(tuple2_attributes);

      vector<Tuple> tuples;
      tuples.push_back(*tuple1);
      tuples.push_back(*tuple2);

      Table *table = new Table("Clients", tuples);

      return *table;
    }

    Table get_Accounts_Table()
    {
      Attribute *client_id = new Attribute(123, true, "Client Id");
      Attribute *account_id = new Attribute(1, false, "Account Id");
      vector<Attribute> tuple1_attributes;
      tuple1_attributes.push_back(*client_id);
      tuple1_attributes.push_back(*account_id);
      Tuple *tuple1 = new Tuple(tuple1_attributes);

      Attribute *client_id2 = new Attribute(321, true, "Client Id");
      Attribute *account_id2 = new Attribute(2, false, "Accoutnt Id");
      vector<Attribute> tuple2_attributes;
      tuple2_attributes.push_back(*client_id2);
      tuple2_attributes.push_back(*account_id2);
      Tuple *tuple2 = new Tuple(tuple2_attributes);

      Attribute *client_id3 = new Attribute(555, true, "Client Id");
      Attribute *account_id3 = new Attribute(3, false, "Account Id");
      vector<Attribute> tuple3_attributes;
      tuple3_attributes.push_back(*client_id3);
      tuple3_attributes.push_back(*account_id3);
      Tuple *tuple3 = new Tuple(tuple3_attributes);

      vector<Tuple> tuples;
      tuples.push_back(*tuple1);
      tuples.push_back(*tuple2);
      tuples.push_back(*tuple3);

      Table *table = new Table("Accounts", tuples);

      return *table;
    }

    Table get_Fruit_Table()
    {
      Attribute *supplier_id = new Attribute(42, true, "Supplier Id");
      Attribute *fruit = new Attribute("Bannana", false, "Fruit", 1);
      vector<Attribute> tuple1_attributes;
      tuple1_attributes.push_back(*supplier_id);
      tuple1_attributes.push_back(*fruit);
      Tuple *tuple1 = new Tuple(tuple1_attributes);

      vector<Tuple> tuples;
      tuples.push_back(*tuple1);

      Table *table = new Table("Fruits", tuples);

      return *table;
    }

  };
}