#include "stdafx.h"
#include "CppUnitTest.h"

#include "Tokenizer.cpp"
#include "DB_Engine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Tokenizer_Tests
{
  TEST_CLASS(Tokenizer_Tests)
  {
  public:
		
    //This method pretty much tests consume_Token, get_Token and even the constructor.
    //I realize this after I was going to write the next test. Do you think this should be broken down?
    TEST_METHOD(test_Tokenizer_Consume_Token)
    {

      string commands[] = {"OPEN test1", "CLOSE", "WRITE", "CLOSE WRITE OPEN"};
      Tokenizer tokenizer[4];


      tokenizer[0] = Tokenizer(&commands[0]);
      Assert::IsTrue(tokenizer[0].consume_Token("OPEN"));
      Assert::IsFalse(tokenizer[0].consume_Token("test"));
      Assert::IsTrue(tokenizer[0].get_Token().get_Kind() == "relation name");

      tokenizer[1] = Tokenizer(&commands[1]);
      Assert::IsFalse(tokenizer[1].consume_Token("OPEN"));
      Assert::IsFalse(tokenizer[1].consume_Token("test"));
      Assert::IsTrue(tokenizer[1].get_Token().get_Kind() == "command");

      tokenizer[2] = Tokenizer(&commands[2]);
      Assert::IsFalse(tokenizer[2].consume_Token("OPEN"));
      Assert::IsTrue(tokenizer[2].consume_Token("WRITE"));
      Assert::IsTrue(tokenizer[2].get_Token().get_Value().empty());

      tokenizer[3] = Tokenizer(&commands[3]);
      Assert::IsTrue(tokenizer[3].consume_Token("CLOSE"));
      Assert::IsTrue(tokenizer[3].consume_Token("WRITE"));
      Assert::IsFalse(tokenizer[3].get_Token().get_Value().empty());
  
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

      Attribute *client_ida3 = new Attribute(5, true, "Client Id");
      Attribute *account_id3 = new Attribute(3, false, "Account Id");
      vector<Attribute> tuple3a_attributes;
      tuple3a_attributes.push_back(*client_ida3);
      tuple3a_attributes.push_back(*account_id3);
      Tuple *tuple3_accounts = new Tuple(tuple3a_attributes);

      engine->create_Table("Clients", *tuple1);
      engine->create_Table("Accounts", *tuple1_accounts);

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
        if(i.get_Name() == table_Name){
          return i;
        }
      }

      return Table("",Tuple());
    }


  };
}

