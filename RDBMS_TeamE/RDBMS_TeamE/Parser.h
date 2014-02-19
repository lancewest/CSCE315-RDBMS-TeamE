#pragma once

#include "Tokenizer.h"
#include "DB_Engine.h"

#include <iostream>

using namespace std;

class DB_Engine;

class Parser {
private:
  Tokenizer tokenizer;
  string command;
  DB_Engine* db;
  string new_relation;

  vector<string> attributes;       // holds attribute lists 
  vector<Attribute> typed_attributes; // holds typed attribute lists
  vector<Attribute> primes;
  //vector<Type> types;

public:
  Parser(DB_Engine* db_ptr, string c);
    
  // The application will function with a bare minimum of create, insert, and select.


	// main parsing function
	// some parsing functions return a bool to indicate a sucessfull parse
	// others return data that is the result of the parse
  bool parse();
  
	// parsing helper functions, called by parse()
  // query parsing functions
  pair<bool, Table> parse_Query();

  string parse_Relation();

  bool parse_Identifier();
  pair<bool, Table> parse_Expression();
  bool parse_Atomic();

  //Parses Conditions for Select, Update and Delete
  pair<bool, vector<Condition>> parse_Condition_List();

  bool parse_Conjunction();
  bool parse_Comparison();
    
  string parse_Op();
  string parse_Attribute_Name();

  pair<bool,string> parse_Attribute();
  pair<bool,vector<string>> parse_Attribute_List();

  //command parsing functions
  bool parse_Command();
  pair< bool, vector<pair<string,string>> > parse_Assignment_List();
  pair<bool, pair<string,string>> parse_Assignment();

  pair<bool,Attribute> parse_Literal();
  pair<bool,vector<Attribute>> parse_Literal_List();

  //Attributes parseing function used to insert, rename, and update
  pair<bool, Attribute> parse_Typed_Attribute();
  pair<bool,Tuple> parse_Typed_Attribute_List();

  bool parse_Var_Type();
  bool parse_Int_Type();

  bool isid(string id); //helper function tests for valid identifier names, needs implementation currently returns true
};
