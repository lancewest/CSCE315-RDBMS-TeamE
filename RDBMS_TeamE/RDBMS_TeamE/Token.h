#pragma once

#include <string>

using namespace std;

class Token
{
private:
  string value;
  string kind;
public:
  Token(string v, string k);
  string get_Value();
  string get_Kind();
  void set_Kind(string new_kind);
};