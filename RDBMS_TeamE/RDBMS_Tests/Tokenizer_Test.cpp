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

  };
}

