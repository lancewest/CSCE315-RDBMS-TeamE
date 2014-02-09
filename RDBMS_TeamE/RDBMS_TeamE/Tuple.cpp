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

bool Tuple::operator==(Tuple tuple){
  return this->attributes == tuple.get_Attributes();
}

bool Tuple::operator!=(Tuple tuple){
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