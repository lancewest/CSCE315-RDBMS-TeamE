#include "Simple_Parser.h"

Simple_Parser::Simple_Parser(): db() {}

vector<Attribute> Simple_Parser::get_Attributes(string input)
{
  vector<Attribute> attributes;

  // start index of attribute name
  int start = 1;
  int end = input.find(" ");
  int length = end - start;

  string name = input.substr(start, length);
    
  start = input.find(" ") + 1;
  end = input.find(")");
  length = end - start;

  string type_str = input.substr(start, length);

  cout << "Attribute Name: " << name << endl;
  cout << "Attribute Type: " << type_str << endl;
    
  //extract type data from string
  if(type_str == "INTEGER") {
  }
  else { // type is a VARCHAR, get size
    int start = input.find('(');
    int end = input.find(')');
    int length = end - start;

    string size_str = type_str.substr(start, length);
    cout << "Size: " << size_str << endl;
  }
  
  return attributes;
}

bool Simple_Parser::parse(string input)
{
  // CREATE
  if(input[0] == 'C') {
    //process Create Table

    //First we extract the table name
    int start = 13;
    int end = (int) input.find('(') - 1; // name ends two spaces before first open paren
    int length = end - start;
    string name = input.substr(start, length);
          
    cout << "Name string: " << input.substr(start, length) << endl;

    //Then we get the Attributes, for now assume one attribute
    vector<Attribute> attributes;
    start = input.find("(");
    end = input.find('P') - 1;
    length = end - start;
    string attr_string = input.substr(start, length);
          
    cout << "Attr string: " << input.substr(start, length) << endl;
    attributes = this->get_Attributes(input.substr(start, end));

    //Then we get the Primary Keys, this is not critical and can be done later
  
    db.create_Table(name);
	}
  //SHOW
  else if(input[0] == 'S') {
    //extract string name and call db show function
    string name;
    int start = 5;
    int end = (int) input.find(';') - 1;
    int length = end - start;
    name = input.substr(start, length);    
    cout <<"Name of table: "<< name << '\n';
          
    //make the call
          
    int table_loc = db.find(name);
    if (table_loc > 0) {
      db.show(db.get_Tables()[table_loc]);
    }
  }

  //INSERT
  else if(input[0] == 'I') {    
    //first we extract the name
    int start = 12;
    int end = start;
    while(input[end] != ' ') end++;
    int length = end - start;
    string name = input.substr(start, length);
          
    //then extract the values, for now assume one value
          
    start = start + length + 14;
    if (input[start+1] = '"') {
      start += 1;
      end = start + 1;

      while(input[end] != '"') {
        ++end;
      }

      length = end - start;
      name = input.substr(start, length);

      cout<< name << '\n';

      Attribute temp_attribute = Attribute(name, false, "name", name.size());
      vector<Attribute> temp_attributes;
      temp_attributes.push_back(temp_attribute);

      Tuple temp_tuple = Tuple(temp_attributes);
      db.insert(*(db.get_Table(name)), temp_tuple);
    }
    //end = (int) input.find(
    // then make dbengine call
  }

  // SELECT
  else {
  }

  return true;
}