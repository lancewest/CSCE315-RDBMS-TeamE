#pragma once

#include "Table.h"

class DB_Engine
{
private:
  vector<Table> tables;
public:
  void create_Table(string name);
    
  void open(string directory); //opens and imports the SQL of all files in a directory into our object structure (Tables, Attributes, Tuples)
  void write(Table table);     //Writes a given table into SQL instruction to a file in the database

  void close(); //Closes the current database session

  void show(Table table); // Shows requested table
  void update(Table table, string attr_name, Attribute attr, bool (*f)(Attribute)); //Updates an attribute in a given table and row.
  void insert(Table table, Tuple tuple); //Inserts a new Tuple into a Table
 
  void erase(Table table);              //Deletes an entire Table
  void erase(Table table, Tuple tuple); //Deletes a Tuple in a Table

  Table select(Table table, string attr_name, bool (*f) (Attribute)); //Returns a table containing only the tuples satisfying the condition f
  Table project(Table table, Tuple attributes); //Returns a Table which is the projection of a table over a list of attributes

  Table rename(vector<string> new_attr_names, Table table); //Replaces the attribute names in the table with new_attribute_names

  Table union_Tables(Table table1, Table table2);      //Returns a Table that is the union of two Tables
  Table difference_Tables(Table table1, Table table2); //returns the difference between two Tables
  Table cartessian_Tables(Table table1, Table table2); //Returns a table that is the cartesian product of two tables
  Table natural_Join(Table table1, Table table2);      //Return a new table representing the natural join of the two argument tables

  int find(string name); //finds a table in the tables vector by its name

  vector<Table> get_Tables() const;
};
