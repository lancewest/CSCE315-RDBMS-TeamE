//class Tokenizer, tokenizes a string
#pragma once

#include "Token.h"

#include <cctype>
#include <string>
#include <vector>

using namespace std;

class Tokenizer
{
private:
  int index;      //current index in token stream
  int position;
  int point;
  vector<Token> tokens;
  bool match(string* text, int position , string exp);
  string get_Integer(string* text, int position);
  string get_Varchar(string* text, int position);

public:
  //constructor actually does the Tokenizer
  Tokenizer(string* text);
  Tokenizer();
  bool consume_Token(string in); //consumes a token if in matches the token
  Token get_Token();            //returns current token in stream
  void checkpoint();             //set a chekpoint to back up to 
  void back_Up();
  void increase_Index(int addend = 1);
  bool is_One_Valid_Line();
};