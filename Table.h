#pragma once

#include "Tuple.h"

class Table
{
private:
  string name;
  vector<Tuple> tuples;
public:
  Table();
  Table(string n); 
  Table(string n, vector<Tuple> t);

  /*************************************************************************
  Eliezer Cabrera: The following code is beyond what I have to write for now
  *************************************************************************/

  //Returns a Table that is the union of two Tables
  Table operator+(Table table);

  //returns the difference between two Tables
  Table operator-(Table table);

  //Returns a table that is the cartesian product of two tables
  Table operator*(Table table);
  
  //copies a table to a new table
  Table operator=(Table table);

  //Inserts a new Tuple into a Table
  void insert(Tuple new_tuple);
   
  //Deletes a Tuple in a Table
  void remove(Tuple tuple_name);

  //Returns Table name
  string get_Name();

  //Returns the Tuples vector
  vector<Tuple> get_Tuples();

  void show();

  //Returns the column corresponding to that attribute name in the table
  vector<Attribute> get_Column(string attr_name);

  // returns 0 if the attribute is successfully changed, 1 for failure
  int replace_Attribute(string attr_name, Attribute attr, int tuple);
};

