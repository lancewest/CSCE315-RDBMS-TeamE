#pragma once

#include "DB_Engine.h"
#include "Parser.h"
#include <fstream>
#include <algorithm>


DB_Engine::DB_Engine() : tables() { }

void DB_Engine::parse(string s)
{
  Parser parser(this, s);
  parser.parse();
}

void DB_Engine::create_Table(string name, Tuple template_tuple)
{
  Table new_table = Table(name, template_tuple);
  this->tables.push_back(new_table);
}

void DB_Engine::add_Table(Table* table)
{
  tables.push_back(*table);
}

bool DB_Engine::open(string directory)
{
  ifstream my_read_file;
  my_read_file.open(directory.c_str());

  if (my_read_file.is_open()) {
    cout << "File opened." << endl;
    string output;

    bool ret = true;
    while (getline(my_read_file, output, ';')) {
      output.push_back(';');
      //cout << output << endl;
      Parser open_file = Parser(this, output);
    
      ret = open_file.parse() ;

      if(!ret)
        return ret;
      
    }
    return ret;
  }
  else {
    cout << "Error: Invalid File Name!" << endl;
    return false;
  }
}

void DB_Engine::write(Table table)
{
  ofstream ofs(table.get_Name().data(), std::ios::out);
  vector<Attribute> attributes = table.get_Tuples().front().get_Attributes();

  ofs << "CREATE TABLE " << table.get_Name() << " (";

  for(auto i = attributes.begin(); i != attributes.end(); ++i) {
    if(i->is_Varchar()) {
      ofs << i->get_Name() << " VARCHAR(" << i->get_Length() << ")";
    }

    if(i->is_Int()) {
      ofs << i->get_Name() << " INTEGER";
    }

    if(attributes.end() - i != 1) {
      ofs << ", ";
    }

    else {
      ofs << ") ";
    }
  }

  ofs << "PRIMARY KEY (";

  bool first = true;
  for(auto i = attributes.begin(); i != attributes.end(); ++i) {

    if(i->is_Primary()) {

      if(!first)
        ofs << " ,";

      ofs << i->get_Name();
      first = false;
    }

    if(attributes.end() - i == 1) {
      ofs << ");";
    }
  }

  ofs << endl;

  for(Tuple& i: table.get_Tuples()) {
    ofs << "INSERT INTO " << table.get_Name() << " VALUES FROM " << i << endl;
  }

  //cout << "WRITE " << table.get_Name() << ";" << endl;
  //cout << "CLOSE " << table.get_Name() << ";" << endl;
  //cout << "EXIT" << ";" << endl;
}

void DB_Engine::show(Table table)
{
  cout << endl;
  table.show();
  cout << endl;
}

//Set attributes listed in pair.first of assignments to the value in pair.second
//But only if the all of the attributes in a single tuple follow any conditions that may apply to that specific attribute
void DB_Engine::update(Table& table, vector<pair<string,string>> assignments, vector<Condition> conditions)
{
  for(Tuple& t : table.tuples)
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

void DB_Engine::erase(Table& table, vector<Condition> conditions)
{
  vector<Tuple> to_delete = vector<Tuple>();

  for(Tuple& t : table.tuples)
  {
    if(this->tuple_Meets_Conditions(t,conditions)){
      to_delete.push_back(t);
    }
  }

  for(Tuple t : to_delete)
  {
    erase(table, t);
  }
}

// selects all tuples whose attributes pass the testing function f, older implementation kept for possible future use
Table DB_Engine::select(Table table, string attr_name, bool (*f) (Attribute))
{
  vector<Tuple> tuples = vector<Tuple>();

  for(Tuple& i: table.get_Tuples()) {
    for(Attribute& j: i.get_Attributes()) {
	  if(j.get_Name() == attr_name && f(j)) {
      tuples.push_back(i);
	  }
	}
  }

  if(tuples.size() == 0)
    return Table("Empty Table", Tuple());

  return Table( "New Table", tuples[0], tuples);
}

// selects all tuples from table that meet conditions
Table DB_Engine::select(Table table, vector<Condition> conditions)
{
  vector<Tuple> selected = vector<Tuple>();

  for(Tuple& t : table.tuples)
  {
    if(this->tuple_Meets_Conditions(t,conditions)){
      selected.push_back(t);
    }
  }

  if(selected.size() == 0)
    return Table("Empty Table", Tuple());

  return Table( "Selection", selected[0], selected );
}

Table DB_Engine::project(Table table, Tuple attributes)
{
  vector<Tuple> new_tuples;
  vector<Attribute> selected_attributes = vector<Attribute>();

  for(Tuple t : table.get_Tuples()){
    for(Attribute a : t.get_Attributes()) {
      for(Attribute wanted : attributes.get_Attributes()) {
        if(a.get_Name() == wanted.get_Name())
        {
          selected_attributes.push_back(a);
          break;
        }
      }
    }
    new_tuples.push_back( Tuple(selected_attributes) );
    selected_attributes = vector<Attribute>();
  }

  for(auto i = new_tuples.begin(); i != new_tuples.end(); ++i) {
    new_tuples.erase(remove(i+1, new_tuples.end(), *i), new_tuples.end());
  }

  if(new_tuples.size() == 0)
    return Table("Empty Projected", Tuple(), new_tuples);

  return Table("projected", new_tuples[0], new_tuples);
}

// changes the name of every attribute
Table DB_Engine::rename(vector<string> names, Table table)
{
  vector<Tuple> tuples = vector<Tuple>();

  for(Tuple& i: table.get_Tuples()) {

    vector<Attribute> new_attributes = vector<Attribute>();
    for(int j = 0; j<i.get_Attributes().size(); j++) {

      Attribute new_attribute = i.get_Attributes()[j];
      new_attribute.set_Name(names[j]);
      new_attributes.push_back(new_attribute);
    }

    tuples.push_back( Tuple(new_attributes) );
  }
  
  if(tuples.size() == 0)
    return Table(table.get_Name(), Tuple(), tuples);

  return Table(table.get_Name(), tuples[0], tuples);
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
        vector<Attribute> new_tuple_attributes = tuple1.get_Attributes();

        for(Attribute a : tuple2.get_Attributes()){
          bool unique = true;

          for(Attribute common_a : common_attributes){
            if(a.is_Compatible(common_a) ){
                unique = false;
                break;
            }
          }

          if(unique){
            new_tuple_attributes.push_back(a);
		      }
        }
        new_tuples.push_back( Tuple(new_tuple_attributes) );
      }
    }
  }

  Table *joined = new Table(table1.get_Name() + " joined with " + table2.get_Name(), new_tuples[0], new_tuples);

  return *joined;
}

//Helper function to Natural Join
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
  bool conditions_met = attribute_Meets_Condition(t, t.get_Attribute_Copy(conditions[0].attribute), conditions[0] );

  for(int i = 1 ; i<conditions.size() ; i++) {

    if(conditions[i-1].conjunction == "&&")
      conditions_met = conditions_met && attribute_Meets_Condition(t, t.get_Attribute_Copy(conditions[i].attribute), conditions[i] );
    else if(conditions[i-1].conjunction == "||")
      conditions_met = conditions_met || attribute_Meets_Condition(t, t.get_Attribute_Copy(conditions[i].attribute), conditions[i] );
  }

  return conditions_met;
}

bool compare_Int_To_Condition(int value, Condition c)
{
  int c_value = atoi(c.value.c_str());

  if(c.compare_operator == "=="){
    if(value == c_value)
      return true;
    else
      return false;
  }
  else if(c.compare_operator == "!="){
    if(value != c_value)
      return true;
    else
      return false;
  }
  else if(c.compare_operator == "<="){
    if(value <= c_value)
      return true;
    else
      return false;
  }
  else if(c.compare_operator == ">="){
    if(value >= c_value)
      return true;
    else
      return false;
  }
  else if(c.compare_operator == "<"){
    if(value < c_value)
      return true;
    else
      return false;
  }
  else if(c.compare_operator == ">"){
    if(value > c_value)
      return true;
    else
      return false;
  }
}

bool compare_String_To_Condition(string value, Condition c)
{
  string c_value = c.value;

  if(c.compare_operator == "=="){
    if(value == c_value)
      return true;
    else
      return false;
  }
  else if(c.compare_operator == "!="){
    if(value != c_value)
      return true;
    else
      return false;
  }
  else if(c.compare_operator == "<="){
    if(value <= c_value)
      return true;
    else
      return false;
  }
  else if(c.compare_operator == ">="){
    if(value >= c_value)
      return true;
    else
      return false;
  }
  else if(c.compare_operator == "<"){
    if(value < c_value)
      return true;
    else
      return false;
  }
  else if(c.compare_operator == ">"){
    if(value > c_value)
      return true;
    else
      return false;
  }
}

bool DB_Engine::attribute_Meets_Condition(Tuple t, Attribute a, Condition c)
{
  //If condition is comparing to non-literal
  if(!c.is_literal) {
    for(Attribute i : t.get_Attributes()) {
      if(i.get_Name() == c.value) {
        if(a.is_Int())
        {
          c.value = to_string(i.get_Int_Value());
          return compare_Int_To_Condition(a.get_Int_Value(), c);
        }
        else
        {
          c.value = i.get_String_Value();
          return compare_String_To_Condition(a.get_String_Value(), c);
        }
      }
    }

    cout << "Error: passed in non-existent attribute name as operand!\n";
    return false;
  }

  //If condition is comparing to non-literal
  if(a.is_Int()) //attribute a is int based
  {
    return compare_Int_To_Condition(a.get_Int_Value(), c);
  }
  else //attribute a is string based
  {
    return compare_String_To_Condition(a.get_String_Value(), c);
  }

  return true;
}

void DB_Engine::make_Assignments(Tuple& t, vector<pair<string,string>> assignments)
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
