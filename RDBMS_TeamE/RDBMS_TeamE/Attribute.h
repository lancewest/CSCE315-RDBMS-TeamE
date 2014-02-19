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
  Attribute();
  bool operator==(Attribute attribute) const;
  bool operator!=(Attribute attribute) const;
  void show() const; // used to display contents of database and debugging
  bool is_Primary() const;
  bool is_Int() const;
  bool is_Varchar() const;
  bool is_Compatible(Attribute attribute) const;
  string get_Name() const;
  void set_Name(string new_name);
  string get_String_Value();
  int get_Int_Value();
  int get_Length();
  void set_String_Value(string val);
  void set_Int_Value(int val);
  void set_Is_Primary(bool val);
  void set_Length(int l);
};

inline ostream& operator<<(ostream& os, Attribute& a)
{
  if(a.is_Int()) {
    os << a.get_Int_Value();
  }
  if(a.is_Varchar()) {
    os << "\"" << a.get_String_Value() << "\"";
  }

  return os;
}