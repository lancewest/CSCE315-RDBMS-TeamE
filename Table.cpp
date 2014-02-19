#include "Table.h"

//Assume all tuples have the same types, might check this later

Table::Table() : name(""), tuples() {}

Table::Table(string n) : name(n), tuples() {}

Table::Table(string n, vector<Tuple> t) : name(n), tuples(t) {}

  /******************************************************************************
  Eliezer Cabrera: The remaining functions are dummy functions, except get_Name()
  ******************************************************************************/

Table Table::operator+(Table table) {}

Table Table::operator-(Table table) {}

Table Table::operator*(Table table) {}
  
Table Table::operator=(Table table) {}

void Table::insert(Tuple new_tuple) {}
   
void Table::remove(Tuple tuple_name) {}

string Table::get_Name()
{
  return this->name;
}

vector<Tuple> Table::get_Tuples() {}

void Table::show() {}

vector<Attribute> Table::get_Column(string attr_name) {}

int Table::replace_Attribute(string attr_name, Attribute attr, int tuple) {}