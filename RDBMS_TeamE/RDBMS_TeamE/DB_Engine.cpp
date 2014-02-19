#pragma once

#include "DB_Engine.h"
#include "Parser.h"
#include <fstream>


DB_Engine::DB_Engine() : tables() { }

void DB_Engine::create_Table(string name, Tuple template_tuple)
{
  Table new_table = Table(name, template_tuple);
  this->tables.push_back(new_table);
}


void DB_Engine::open(string directory)
{
  ifstream my_read_file;
  my_read_file.open(directory.c_str());

  if (my_read_file.is_open()) {
    cout << "File opened." << endl;
    string output;

    while (getline(my_read_file, output, ';')) {
      output.push_back(';');
      cout << output << endl;
      Parser open_file = Parser(this, output);
    
      bool ret = open_file.parse();

      cout << ret << endl;
    }
  }
}

void DB_Engine::write(Table table)
{
  ofstream ofs(table.get_Name().data(), std::ios::out);
  vector<Attribute> attributes = table.get_Tuples().front().get_Attributes();

  cout << "CREATE TABLE " << table.get_Name() << " (";

  for(auto i = attributes.begin(); i != attributes.end(); ++i) {
    if(i->is_Varchar()) {
      cout << i->get_Name() << " VARCHAR(" << i->get_Length() << ")";
    }

    if(i->is_Int()) {
      cout << i->get_Name() << " INTEGER";
    }

    if(attributes.end() - i != 1) {
      cout << ", ";
    }

    else {
      cout << ") ";
    }
  }

  cout << "PRIMARY KEY (";

  for(auto i = attributes.begin(); i != attributes.end(); ++i) {

    if(i != attributes.begin()) {
      cout << ", ";
    }

    if(i->is_Primary()) {
      cout << i->get_Name();
    }

    if(attributes.end() - i == 1) {
      cout << "\b\b";
      cout << ");";
    }
  }

  cout << endl;

  for(Tuple& i: table.get_Tuples()) {
    cout << "INSERT INTO " << table.get_Name() << " VALUES FROM " << i << endl;
  }

  //cout << "WRITE " << table.get_Name() << ";" << endl;
  //cout << "CLOSE " << table.get_Name() << ";" << endl;
  //cout << "EXIT" << ";" << endl;
}

void DB_Engine::show(Table table)
{
  table.show();
}

//Set attributes listed in pair.first of assignments to the value in pair.second
//But only if the all of the attributes in a single tuple follow any conditions that may apply to that specific attribute
void DB_Engine::update(Table& table, vector<pair<string,string>> assignments, vector<Condition> conditions)
{
  for(Tuple& t : table.get_Tuples())
  {
    if(this->tuple_Meets_Conditions(t,conditions)){
      this->make_Assignments(t, assignments);
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
  Table new_table("New Table", table.get_Template_Tuple());

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
  
  Table *new_table = new Table(table.get_Name() + " Projection", table.get_Template_Tuple(), new_tuples);

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
  
  return table;
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

  Table *joined = new Table(table1.get_Name() + " joined with " + table2.get_Name(), table1.get_Template_Tuple(), new_tuples);

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

void DB_Engine::close(string relation_name)
{
  erase( *(this->get_Table(relation_name)) );
}

void DB_Engine::exit()
{
  tables.clear();
}

int DB_Engine::find(string name)
{
  vector<Table> tables = this->get_Tables();
  for(int i = 0; i < tables.size(); ++i) {
    if(tables[i].get_Name() == name) {
	    return i;
    }
  }
	return -1;
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

bool DB_Engine::tuple_Meets_Conditions(Tuple t, vector<Condition> conditions)
{
  bool conditions_met; 

  for(Attribute a : t.get_Attributes()){
    conditions_met = attribute_Meets_Condition(a,conditions[0]);

    for(int i = 1 ; i<conditions.size() ; i++) {

      if(conditions[i].conjunction == "&&")
        conditions_met = conditions_met && attribute_Meets_Condition(a,conditions[i]);
      else if(conditions[i].conjunction == "||")
        conditions_met = conditions_met || attribute_Meets_Condition(a,conditions[i]);
      else
        cout << "Error: DB_Engine, ln 306";
    }
  }
  return conditions_met;
}

bool DB_Engine::attribute_Meets_Condition(Attribute a, Condition c)
{
  if(a.get_Name() != c.attribute) //Condition not for this attribute
      return true;

  if(a.is_Int()) //attribute a is int based
  {
    int value = atoi(c.value.c_str());

    if(c.compare_operator == "=="){
      if(a.get_Int_Value() == value)
        return true;
      else
        return false;
    }
    else if(c.compare_operator == "!="){
      if(a.get_Int_Value() != value)
        return true;
      else
        return false;
    }
    else if(c.compare_operator == "<="){
      if(a.get_Int_Value() <= value)
        return true;
      else
        return false;
    }
    else if(c.compare_operator == ">="){
      if(a.get_Int_Value() >= value)
        return true;
      else
        return false;
    }
    else if(c.compare_operator == "<"){
      if(a.get_Int_Value() < value)
        return true;
      else
        return false;
    }
    else if(c.compare_operator == ">"){
      if(a.get_Int_Value() > value)
        return true;
      else
        return false;
    }
  }
  else //attribute a is string based
  {
    if(c.compare_operator == "=="){
      if(a.get_String_Value() == c.value)
        return true;
      else
        return false;
    }
    else if(c.compare_operator == "!="){
      if(a.get_String_Value() != c.value)
        return true;
      else
        return false;
    }
    else if(c.compare_operator == "<="){
      if(a.get_String_Value() <= c.value)
        return true;
      else
        return false;
    }
    else if(c.compare_operator == ">="){
      if(a.get_String_Value() >= c.value)
        return true;
      else
        return false;
    }
    else if(c.compare_operator == "<"){
      if(a.get_String_Value() < c.value)
        return true;
      else
        return false;
    }
    else if(c.compare_operator == ">"){
      if(a.get_String_Value() > c.value)
        return true;
      else
        return false;
    }
  }

  return true;
}

void DB_Engine::make_Assignments(Tuple t, vector<pair<string,string>> assignments)
{
  for(pair<string,string> assign : assignments)
  {
    Attribute* attribute = t.get_Attribute(assign.first);

    if(attribute->is_Int())
      attribute->set_Int_Value( atoi(assign.second.c_str()) );
    else
      attribute->set_String_Value(assign.second);
  }
}
