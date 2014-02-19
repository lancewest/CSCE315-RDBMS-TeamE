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
    TEST_METHOD(test_Parse_Command)
    {
      vector<string> commands;
        commands.push_back("CREATE TABLE animals (name VARCHAR(20), kind VARCHAR(8), years INTEGER) PRIMARY KEY (name, kind);");
        commands.push_back("INSERT INTO animals VALUES FROM (\"Joe\", \"bird\", 2);");
        commands.push_back("SHOW animals;");
        commands.push_back("INSERT INTO species VALUES FROM RELATION project (kind) animals;");
        commands.push_back("SHOW answer;");
        commands.push_back("UPDATE animals SET (kind = \"lion\") WHERE name == (\"Joe\");");
        commands.push_back("WRITE animals;");
        commands.push_back("CLOSE animals;");

      DB_Engine* db = new DB_Engine();

      for(string& i: commands) {
        Parser parser(db, i);

        //I think this is how you would extract the bool from parse() when implemented
        Assert::IsTrue(parser.parse().first);
      }
    }

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
        Assert::IsTrue(parser.parse().first);
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
        Assert::IsTrue(parser.parse().first);
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
        Assert::IsTrue(parser.parse().first);
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
        Assert::IsTrue(parser.parse().first);
      }
    }

    TEST_METHOD(test_Parse_Querry)
    {
      vector<string> querries;
        querries.push_back("a <- rename (aname, akind) (project (name, kind) animals);");

        //Just noticed that aparently the result of multiplying two tables has different attribute names
        //for commond attributes. It seems that the attributes from relation "a" are called a[INSERT NAME OF ATTRIBUTE]
        //as in aname instead of name, or akind instead of kind. I don't think we've done this.
        querries.push_back("common_names <- project (name) (select (aname == name && akind != kind) (a * animals));");
        querries.push_back("answer <- common_names;");

      DB_Engine* db = new DB_Engine();

      for(string& i: querries) {
        Parser parser(db, i);

        //I think this is how you would extract the bool from parse() when implemented
        Assert::IsTrue(parser.parse().first);
      }
    }

  };
}

