#pragma once

#include "DB_Engine.h"
#include <fstream>


void DB_Engine::create_Table(string name)
{
  Table new_table = Table(name);
  this->tables.push_back(new_table);
}


void DB_Engine::open(string directory)
{
  //Not needed for first deliverable
}

void DB_Engine::write(Table table)
{
  //Not needed for first deliverable
}

void DB_Engine::show(Table table)
{
  table.show();
}

//Set attributes in column attr_name to attr if they pass the test function f
//only updates one attribute at a time
void DB_Engine::update(Table table, string attr_name, Attribute attr, bool (*f)(Attribute))
{
  vector<Attribute> attributes = table.get_Column(attr_name);

  for(unsigned int i = 0; i < attributes.size(); ++i) {
    if( (*f)(attributes[i]) ) {
	  table.replace_Attribute(attr_name, attr, i);
	}
  }
}

void DB_Engine::insert(Table table, Tuple tuple)
{
  for(Table& i: this->get_Tables()) {
    if(i.get_Name() == table.get_Name()) {
      i.insert(tuple);
	}
  }
}

void DB_Engine::erase(Table table)
{
  for(auto i = this->tables.begin(); i != this->tables.end(); ++i){
    if(i->get_Name() == table.get_Name()) {
      this->tables.erase(i);
	  i = this->tables.begin();
	}
  }
}

void DB_Engine::erase(Table table, Tuple tuple)
{
  for(Table& i: this->tables){
    if(i.get_Name() == table.get_Name()) {
      i.remove(tuple);
	}
  }
}

// selects all tuples whose attributes pass the testing function f
Table DB_Engine::select(Table table, string attr_name, bool (*f) (Attribute))
{
  Table new_table;

  for(Tuple& i: table.get_Tuples()) {
    for(Attribute& j: i.get_Attributes()) {
	  if(j.get_Name() == attr_name && f(j)) {
	    new_table.insert(i);
	  }
	}
  }

  return new_table;
}

Table DB_Engine::project(Table table, Tuple attributes)
{
  Table new_table;
  vector<vector<Attribute> > columns;

  for(Attribute& i: attributes.get_Attributes()) {
    columns.push_back(table.get_Column(i.get_Name()));
  }

  for(vector<Attribute>& i: columns) {
    Tuple current_row;
	for(Attribute& j: i) {
	  current_row = current_row + i;
	}
	new_table.insert(current_row);
  }

  return new_table;
}

// changes the name of every attribute
Table DB_Engine::rename(vector<string> names, Table table)
{
  //NOT IMPLEMENTED: FUNCTION NOT NEEDED FOR CURRENT DELIVERABLE
  /*Table new_table;

  for(Tuple& i: table.get_Tuples()) {
    for(Attribute& j: i.get_Attributes()) {
	  j.set_Name(names

  return new_table;*/
  Table t;
  return t;
}

Table DB_Engine::union_Tables(Table table1, Table table2)
{
  return table1 + table2;
}

Table DB_Engine::difference_Tables(Table table1, Table table2)
{
  return table1 - table2;
}

Table DB_Engine::cartessian_Tables(Table table1, Table table2)
{
  return table1*table2;
}

Table DB_Engine::natural_Join(Table table1, Table table2)
{
  //NOT IMPLEMENTED
  Table t;
  return t;
}

void DB_Engine::close()
{
  //Not needed for current deliverable
}

int DB_Engine::find(string name)
{
  /*Not needed for current deliverable
  for(Table& i: this->get_Tables()) {
    if(i.get_Name() = name) {
	  return 

  for(int i = 0; i < tables.size(); i++) {
    if (tables[i].get_Name() == name) {
	  return i;
	}
  }
  return -1;
  */

	return 1;
}

vector<Table> DB_Engine::get_Tables() const
{
  return this->tables;
}
