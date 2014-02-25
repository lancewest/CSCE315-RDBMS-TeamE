#pragma once

#include "Table.h"
#include "Tuple.h"
#include "Condition.h"

class DB_Engine
{
private:
  vector<Table> tables;
public:
  DB_Engine();

  void parse(string s);

  void create_Table(string name, Tuple template_tuple);
  void add_Table(Table* table);
    
  bool open(string directory); //opens and imports the SQL of all files in a directory into our object structure (Tables, Attributes, Tuples)
  void write(Table table);     //Writes a given table into SQL instruction to a file in the database

  void close(string relation_name); //Closes the given table
  void exit(); //Closes the current database session

  void show(Table table); // Shows requested table
  void update(Table& table, vector<pair<string,string>> assignments, vector<Condition> conditions); //Updates all attributes specified by 'assignments' in all tuples that meet 'conditions'
  void insert(Table table, Tuple tuple); //Inserts a new Tuple into a Table
 
  void erase(Table table);              //Deletes an entire Table
  void erase(Table table, Tuple tuple); //Deletes a Tuple in a Table
  void erase(Table& table, vector<Condition> conditions); //Deletes all tuples in a table that match the conditions

  Table select(Table table, string attr_name, bool (*f) (Attribute)); //Returns a table containing only the tuples satisfying the condition f
  Table select(Table table, vector<Condition> conditions); //Returns a table containing only the tuples satisfying all conditions
  Table project(Table table, Tuple attributes); //Returns a Table which is the projection of a table over a list of attributes

  Table rename(vector<string> new_attr_names, Table table); //Replaces the attribute names in the table with new_attribute_names

  Table union_Tables(Table table1, Table table2);      //Returns a Table that is the union of two Tables
  Table difference_Tables(Table table1, Table table2); //returns the difference between two Tables
  Table cartessian_Tables(Table table1, Table table2); //Returns a table that is the cartesian product of two tables
  Table natural_Join(Table table1, Table table2);      //Return a new table representing the natural join of the two argument tables

  int find(string name); //finds a table in the tables vector by its name

  vector<Table> get_Tables() const;
  vector<Attribute> get_Common_Attributes(Table table1, Table table2);
  Table* get_Table(string table_name);
  bool tuple_Meets_Conditions(Tuple t, vector<Condition> c); //Helper for Update and Select
  bool attribute_Meets_Condition(Tuple t, Attribute a, Condition c); //Helper for Update and Select
  void make_Assignments(Tuple& t, vector<pair<string,string>> assignments); //Helper for Update
};
