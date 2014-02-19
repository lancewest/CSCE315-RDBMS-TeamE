#pragma once

#include <string>

using namespace std;

struct Condition
{
public:
  Condition::Condition();
  Condition::Condition(string a, string c, string v, string con);

  string attribute;
  string compare_operator;
  string value;
  string conjunction;
};
