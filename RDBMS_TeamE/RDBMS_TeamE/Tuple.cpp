#include "Tuple.h"

Tuple::Tuple() : attributes() {}

Tuple::Tuple(vector<Attribute> a) : attributes(a) {}

int Tuple::get_Size()
{
  return attributes.size();
}

vector<Attribute> Tuple::get_Attributes()
{
  return this->attributes;
}

bool Tuple::operator==(Tuple tuple)
{
  return this->attributes == tuple.get_Attributes();
}

bool Tuple::operator!=(Tuple tuple)
{
  return !(*this == tuple);
}

Tuple Tuple::operator+(Tuple t)
{
  Tuple new_tuple = *this;
  for(Attribute& i: t.get_Attributes()) {
    new_tuple.attributes.push_back(i);
  }
  return new_tuple;
}

void Tuple::show() {
  for(Attribute& i: this->attributes) {
    i.show();
    cout << "\t";
  }
}

void Tuple::replace_Attribute(string attr_name, Attribute attr)
{
  for(Attribute& i: this->attributes) {
    if(i.get_Name() == attr_name) {
        i = attr;
    }
  }
}

bool Tuple::is_Primarily_Equal(Tuple t)
{
  vector<Attribute> rhs = this->get_Attributes();
  vector<Attribute> lhs = t.get_Attributes();

  if(rhs.size() != lhs.size()) {
    return false;
  }

  for(unsigned int i = 0; i < this->get_Size(); ++i) {
    if( this->get_Attributes()[i].is_Primary() &&
      !(this->get_Attributes()[i].is_Compatible(t.get_Attributes()[i])) ) {
         return false;
    }
  }

  return true;
}

bool Tuple::is_Compatible(Tuple t)
{
  vector<Attribute> rhs = this->get_Attributes();
  vector<Attribute> lhs = t.get_Attributes();

  if(rhs.size() != lhs.size()) {
    return false;
  }

  for(unsigned int i = 0; i < rhs.size(); ++i) {
	if(!rhs[i].is_Compatible(lhs[i])) {
	  return false;
	}
  }

  return true;
}

bool Tuple::equal_On_Keys(Tuple t, vector<Attribute> keys)
{
  for(Attribute a : keys){
    if( *(get_Attribute(a.get_Name())) != *(t.get_Attribute(a.get_Name())) )
      return false;
    }

    return true;
}

Attribute* Tuple::get_Attribute(string attribute_name)
{
  for(Attribute& a : attributes){
    if(a.get_Name() == attribute_name)
      return &a;
  }

  return new Attribute("null",false,"empty_attribute",1);
}

Attribute Tuple::get_Attribute_Copy(string attribute_name)
{
  for(Attribute a : attributes){
    if(a.get_Name() == attribute_name)
      return a;
  }

  return Attribute("null",false,"empty_attribute",1);
}

