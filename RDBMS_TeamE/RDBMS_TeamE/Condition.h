#pragma once

#include <string>

using namespace std;

struct Condition
{
public:
  Condition::Condition(string a, string c, string v, string con, bool l);

  string attribute;
  string compare_operator;
  string value;
  string conjunction;
  bool is_literal;
};
