#include "stdafx.h"
#include "CppUnitTest.h"

#include "Parser.cpp"
#include "DB_Engine.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Parser_Tests
{
  TEST_CLASS(Tokenizer_Tests)
  {
  public:
    //This test also tests queries and expression. Should this be broken downs? 

    TEST_METHOD(test_Parse_Condition_List)
    {
      vector<string> condition_lists;
        condition_lists.push_back("(aname == name && akind != kind)");
        condition_lists.push_back("(aname == name || akind != kind)");
        condition_lists.push_back("(aname == name || akind != kind && kind != name)");

      DB_Engine* db = new DB_Engine();

      for(string& i: condition_lists) {
        Parser parser(db, i);

        //I think this is how you would extract the bool from parse() when implemented
        Assert::IsTrue(parser.parse_Condition_List().first);
      }
    }

    TEST_METHOD(test_Parse_Typed_Attribute_List)
    {
      vector<string> typed_attribute_lists;
        typed_attribute_lists.push_back("(name VARCHAR(20))");
        typed_attribute_lists.push_back("(years INTEGER)");
        typed_attribute_lists.push_back("(name VARCHAR(20), kind VARCHAR(8), years INTEGER)");

      DB_Engine* db = new DB_Engine();

      for(string& i: typed_attribute_lists) {
        Parser parser(db, i);

        //I think this is how you would extract the bool from parse() when implemented
        Assert::IsTrue(parser.parse_Typed_Attribute_List().first);
      }
    }

    TEST_METHOD(test_Parse_Attribute_List)
    {
      vector<string> attribute_lists;
        attribute_lists.push_back("(name, kind)");
        attribute_lists.push_back("(year)");

      DB_Engine* db = new DB_Engine();

      for(string& i: attribute_lists) {
        Parser parser(db, i);

        //I think this is how you would extract the bool from parse() when implemented
        Assert::IsTrue(parser.parse_Attribute_List().first);
      }
    }

    TEST_METHOD(test_Parse_Literal_List)
    {
      vector<string> literal_lists;
        literal_lists.push_back("(\"Michael\")");
        literal_lists.push_back("(42)");
        literal_lists.push_back("(\"Joe\", \"cat\", 4)");

      DB_Engine* db = new DB_Engine();

      for(string& i: literal_lists) {
        Parser parser(db, i);

        //I think this is how you would extract the bool from parse() when implemented
        Assert::IsTrue(parser.parse_Literal_List().first);
      }
    }

    TEST_METHOD(test_Parse)
    {
      DB_Engine* db = new DB_Engine();

      //Read in from file to test all commands and queries
      Assert::IsTrue( db->open("sql.txt") );
    }

    TEST_METHOD(test_Parse_Bad_Syntaxe_1)
    {
      DB_Engine* db = new DB_Engine();

      //Read in from file to test all commands and queries
      Assert::IsFalse( db->open("sql_syntax_error_1.txt") );
    }

    TEST_METHOD(test_Parse_Bad_Syntaxes_2)
    {
      DB_Engine* db = new DB_Engine();

      //Read in from file to test all commands and queries
      Assert::IsFalse( db->open("sql_syntax_error_2.txt") );
    }

    TEST_METHOD(test_Parse_Bad_Syntaxes_3)
    {
      DB_Engine* db = new DB_Engine();

      //Read in from file to test all commands and queries
      Assert::IsFalse( db->open("sql_syntax_error_3.txt") );
    }

    TEST_METHOD(test_Parse_Bad_Syntaxes_4)
    {
      DB_Engine* db = new DB_Engine();

      //Read in from file to test all commands and queries
      Assert::IsFalse( db->open("sql_syntax_error_4.txt") );
    }

    TEST_METHOD(test_Parse_Bad_Syntaxes_5)
    {
      DB_Engine* db = new DB_Engine();

      //Read in from file to test all commands and queries
      Assert::IsFalse( db->open("sql_syntax_error_5.txt") );
    }

    TEST_METHOD(test_Parse_Bad_Syntaxes_6)
    {
      DB_Engine* db = new DB_Engine();

      //Read in from file to test all commands and queries
      Assert::IsFalse( db->open("sql_syntax_error_6.txt") );
    }

    TEST_METHOD(test_Parse_Bad_Syntaxes_7)
    {
      DB_Engine* db = new DB_Engine();

      //Read in from file to test all commands and queries
      Assert::IsFalse( db->open("sql_syntax_error_7.txt") );
    }
  };
}

