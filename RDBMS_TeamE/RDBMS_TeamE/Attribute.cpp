#include "Attribute.h"

Attribute::Attribute(int v, bool p, string n) : int_val(v), is_primary(p), name(n), length(-1) {}

Attribute::Attribute(string v, bool p, string n, int l) : string_val(v), is_primary(p), name(n), length(l){}

bool Attribute::operator==(Attribute attribute) const
{
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

bool Attribute::operator!=(Attribute attribute) const
{
  return !(*this == attribute);
}
  
void Attribute::show() const
{
  if(this->is_Int()) {
    cout << int_val;
  }
  else {
    cout << string_val;
  }
}

bool Attribute::is_Primary() const
{
  return is_primary;
}

bool Attribute::is_Int() const
{
  if(this->length == -1) {
    return true;
  }

  return false;
}

bool Attribute::is_Varchar() const
{
  return !(this->is_Int());
}

bool Attribute::is_Compatible(Attribute attribute) const
{
  if(this->name   == attribute.name &&
     this->length == attribute.length) {
	   return true;
  }
	   
  return false;
}

string Attribute::get_Name() const
{
  return name;
}

void Attribute::set_Name(string new_name)
{
  this->name = new_name;
}

string Attribute::get_String_Value()
{
  return string_val;
}

int Attribute::get_Int_Value()
{
  return int_val;
}

int Attribute::get_Length()
{
  return this->length;
}

void Attribute::set_String_Value(string val)
{
  string_val = val;
}

void Attribute::set_Int_Value(int val)
{
  int_val = val;
}

void Attribute::set_Is_Primary(bool val)
{
  is_primary = val;
}

void Attribute::set_Length(int l)
{
  length = l;
}