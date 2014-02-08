#pragma once

#include "Attribute.h"

class Tuple
{
private:
  vector<Attribute> attributes;
public:
  Tuple();                      // used for empty tuples
  Tuple(vector<Attribute> a);   // used to initialize full tuple
  bool operator==(Tuple t);
  bool operator!=(Tuple t);
  void show(); 
  vector<Attribute> get_Attributes();
  int get_Size();
  void replace_Attribute(string attr_name, Attribute attr);
};

