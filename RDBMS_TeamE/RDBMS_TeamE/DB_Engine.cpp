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
void DB_Engine::update(Table& table, string attr_name, Attribute attr, bool (*f)(Attribute))
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
  for(Table& i: this->tables) {
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
  vector<Tuple> new_tuples;
  
  for(Tuple t : table.get_Tuples()){

    vector<Attribute> selected;
    for(Attribute a : t.get_Attributes()){

      for(Attribute wanted : attributes.get_Attributes()){
        if(a.get_Name() == wanted.get_Name()){
          selected.push_back(a);
        }
      }
    }

    Tuple *new_tuple = new Tuple(selected);
    new_tuples.push_back(*new_tuple);
  }
  
  Table *new_table = new Table(table.get_Name() + " Projection", new_tuples);

  return *new_table;
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
  vector<Attribute> common_attributes = get_Common_Attributes(table1, table2);

  vector<Tuple> new_tuples;

  for(Tuple tuple1 : table1.get_Tuples()){
    for(Tuple tuple2 : table2.get_Tuples()){
      if( tuple1.equal_On_Keys(tuple2, common_attributes) ){
        Tuple *new_tuple = new Tuple(tuple1);

        for(Attribute a : tuple2.get_Attributes()){
          bool unique = true;

          for(Attribute common_a : common_attributes){
            if(a.is_Compatible(common_a) ){
                unique = false;
                break;
            }
          }

          if(unique){
            new_tuples.push_back(*new_tuple);
		  }
        }
      }
    }
  }

  Table *joined = new Table(table1.get_Name() + " joined with " + table2.get_Name(), new_tuples);

  return *joined;
}

vector<Attribute> DB_Engine::get_Common_Attributes(Table table1, Table table2)
{
  vector<Attribute> common_attributes;

  for(Attribute a1 : table1.get_Tuples()[0].get_Attributes()){
    for(Attribute a2 : table2.get_Tuples()[0].get_Attributes()){

      if(a1.is_Compatible(a2)){
        common_attributes.push_back(a1);
      }
    }
  }

  return common_attributes;
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

Table* DB_Engine::get_Table(string table_name)
{
  Table *table = NULL;

  for(Table& t : this->tables){
    if(t.get_Name() == table_name){
      table = &t;
      break;
    }
  }

  return table;
}

vector<Table> DB_Engine::get_Tables() const
{
  return this->tables;
}
