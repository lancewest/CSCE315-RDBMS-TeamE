#include "Attribute.h"

Attribute::Attribute(int v, bool p, string n) : int_val(v), is_primary(p), name(n), length(-1) {}

Attribute::Attribute(string v, bool p, string n, int l) : string_val(v), is_primary(p), name(n), length(l){}

bool Attribute::operator==(Attribute attribute) {
  if(this->is_Int() &&
    this->int_val    == attribute.int_val &&
    this->is_primary == attribute.is_primary &&
    this->name       == attribute.name) {
      return true;
  }

  if(this->is_Varchar() &&
    this->string_val == attribute.string_val &&
    this->is_primary == attribute.is_primary &&
    this->name       == attribute.name &&
    this->length     == attribute.length) {
      return true;
  }

  return false;
}

bool Attribute::operator!=(Attribute attribute) {
  return !(*this == attribute);
}
  
void Attribute::show() {
  if(this->is_Int()) {
    cout << int_val;
  }
  else {
    cout << string_val;
  }
}

bool Attribute::is_Primary()
{
  return is_primary;
}

bool Attribute::is_Int()
{
  if(this->length == -1) {
    return true;
  }

  return false;
}

bool Attribute::is_Varchar()
{
  return !(this->is_Int());
}

string Attribute::get_Name()
{
  return name;
}