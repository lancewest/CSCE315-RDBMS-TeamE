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
  return this->attributes == tuple.attributes;
}

bool Tuple::operator!=(Tuple tuple){
  return !(*this == tuple);
}

void Tuple::show() {
  for(Attribute i: this->attributes) {
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