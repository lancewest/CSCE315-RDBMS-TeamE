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

  vector<string> attributes;       // holds attribute lists 
  vector<Attribute> typed_attributes; // holds typed attribute lists
  vector<Attribute> primes;
  //vector<Type> types;

public:
  Parser(string c);
    
  // The application will function with a bare minimum of create, insert, and select.


	// main parsing function
	// some parsing functions return a bool to indicate a sucessfull parse
	// others return data that is the result of the parse
  bool parse();
  
	// parsing helper functions, called by parse()
  // query parsing functions
  bool parse_Query();

  string parse_Relation();

  bool parse_Identifier();
  bool parse_Expression();
  bool parse_Atomic();

  bool parse_Condition();
  bool parse_Condition_List();

  bool parse_Conjunction();
  bool parse_Comparison();
    
  string parse_Op();
  string parse_Attribute_Name();

  bool parse_Attribute();
  bool parse_Attribute_List();

  //command parsing functions
  bool parse_Command();
  bool parse_Assignment();

  bool parse_Literal();
  bool parse_Literal_List();

  bool parse_Typed_Attribute();
  bool parse_Typed_Attribute_List();

  bool parse_Var_Type();
  bool parse_Int_Type();

  bool isid(string id); //helper function tests for valid identifier names, needs implementation currently returns true
};
