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

  void insert(Tuple new_tuple);          //Inserts a new Tuple into a Table
  bool is_Union_Compatible(Table table); //Checks another table for union compatibility
  Table operator+(Table table);          //Returns a Table that is the union of two Tables
  void remove(Tuple tuple);              //Deletes a Tuple in a Table
  Table operator-(Table table);          //returns the difference between two Tables
  Table operator*(Table table);          //Returns a table that is the cartesian product of two tables

  string get_Name();                     //Returns Table name
  void set_Name(string new_name);        //Sets Table name
  vector<Tuple> get_Tuples();            //Returns the Tuples vector

  void show(); //For debugging

  vector<Attribute> get_Column(string attr_name); //Returns the column corresponding
                                                  //to that attribute name in the table

  // returns 0 if the attribute is successfully changed, 1 for failure
  void replace_Attribute(string attr_name, Attribute attr, int tuple_index);
};