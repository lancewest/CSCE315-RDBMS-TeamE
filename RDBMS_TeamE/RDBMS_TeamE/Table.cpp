#include "Table.h"

#include <algorithm>

Table::Table(string n, Tuple template_t) : name(n), template_tuple(template_t), tuples() { }

Table::Table(string n, Tuple template_t, vector<Tuple> t) : name(n), template_tuple(template_t), tuples() { }

void Table::insert(Tuple new_tuple)
{
  for(Tuple& i: this->tuples) {
    if(!i.is_Primarily_Equal(new_tuple)) {
	  return;
	}
  }

  this->tuples.push_back(new_tuple);
}

bool Table::is_Union_Compatible(Table table)
{
  Tuple lhs = this->get_Tuples().front();
  Tuple rhs = table.get_Tuples().front();

  if(lhs.is_Compatible(rhs)) {
    return true;
  }

  return false;
}

Table Table::operator+(Table table)
{
  Table new_table = *this;
  new_table.set_Name(this->get_Name() + " + " + table.get_Name());

  if(this->is_Union_Compatible(table)) {
    vector<Tuple> tuples = new_table.get_Tuples();

    for(Tuple& i: table.get_Tuples()) {
      if(find(begin(tuples), end(tuples), i) == tuples.cend()) {
	      new_table.insert(i);
	    }
    }
  }
  return new_table;
}

void Table::remove(Tuple tuple)
{
  for(auto i = this->tuples.begin(); i != this->tuples.end(); ++i) {
    if(*i == tuple) {
      this->tuples.erase(i);
	  i = this->tuples.begin();
	}
  }
}

Table Table::operator-(Table table)
{
  Table new_table = *this;
  new_table.set_Name(this->get_Name() + " - " + table.get_Name());


  if(this->is_Union_Compatible(table)) {
    vector<Tuple> tuples = new_table.get_Tuples();

    for(Tuple& i: table.get_Tuples()) {
      if(find(begin(tuples), end(tuples), i) == tuples.cend()) {
	      new_table.remove(i);
	    }
    }
  }
  return new_table;
}

Table Table::operator*(Table table)
{
  Table new_table("New Table", table.get_Template_Tuple());
  new_table.set_Name(this->get_Name() + "*" + table.get_Name());

  for(Tuple& i: this->get_Tuples()) {
    for(Tuple &j: table.get_Tuples()) {
		  new_table.insert(i+j);
	  }
  }

  return new_table;
}

string Table::get_Name()
{
  return this->name;
}

void Table::set_Name(string new_name)
{
  this->name = new_name;
}

vector<Tuple> Table::get_Tuples()
{
  return this->tuples;
}

Tuple Table::get_Template_Tuple()
{
  return template_tuple;
}

void Table::show()
{
  cout << "Table: " << name << "\n";
  for(unsigned int i = 0; i < this->tuples.size(); ++i) {
    cout << i << "Contents: ";
    tuples[i].show();
    cout << "\n";
  }
}

vector<Attribute> Table::get_Column(string attr_name)
{
  vector<Attribute> column;

  for(Tuple& i: this->get_Tuples()) {
    for(Attribute& j: i.get_Attributes()) {
      if(j.get_Name() == attr_name) {
        column.push_back(j);
      }
    }
  }

  return column;
}

//Replaces an attribute of the tuple specified via index
void Table::replace_Attribute(string attr_name, Attribute attr, int tuple_index)
{
  this->tuples[tuple_index].replace_Attribute(attr_name, attr);
}