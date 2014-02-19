#pragma once

#include <vector>
#include <string>
#include <iostream>

using namespace std;

class Attribute
{
private:
  int int_val;
  string string_val;
  int length;
  bool is_primary;
  string name;  // assume attributes have unique names

public:
  Attribute(int v, bool p, string n);
  Attribute(string v, bool p, string n, int l);
  bool operator==(Attribute attribute);
  bool operator!=(Attribute attribute);
  void show(); // used to display contents of database and debugging
  bool is_Primary();
  bool is_Int();
  bool is_Varchar();
  string get_Name();
};