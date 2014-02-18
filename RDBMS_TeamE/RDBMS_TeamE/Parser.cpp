#include "Parser.h"
#include <iostream>

using namespace std;

//constructor
Parser::Parser(string c) : command(c), tokenizer(&c) {}

bool Parser::parse()
{
	return parse_Command() || parse_Query();
}

//-----------------//
//--QUERY PARSING--//
//-----------------//
bool Parser::parse_Query()
{
	this->tokenizer.checkpoint();
  string name = "";
	bool ret = (name = this->parse_Relation()) != ""
	        && this->tokenizer.consume_Token("<-")
	        && this->parse_Expr()
	        && this->tokenizer.consume_Token(";");
	
	if(ret) {
		cout << "Query parsed." << endl;
	}
	else {
		this->tokenizer.back_Up();
		cout << "Query not parsed." << endl;
	}
  return ret;
}

string Parser::parse_Relation()
{
	string s;

	if (this->isid(this->tokenizer.get_Token())) {
	  s = this->tokenizer.get_Token();
	  this->tokenizer.increase_Index();
    return s;
	}

	else return "";
}

bool Parser::parse_Expr()
{
	return this->parse_Projection()
      || this->parse_Selection()
      || this->parse_Renaming()
      || this->parse_Union()
      || this->parse_Difference()
      || this->parse_Product()
	    || this->parse_Atomic();
}

bool Parser::parse_Atomic()
{
	this->tokenizer.checkpoint();
	string name = this->parse_Relation();

	bool ret = name != ""
			    || this->tokenizer.consume_Token("(")
		      && this->parse_Expr()
			    && this->tokenizer.consume_Token(")");

	if(ret) {
    //cout << "Atomic parsed." << endl;
	}
	else {
		this->tokenizer.back_Up();
	}

	return ret;
}

bool Parser::parse_Selection()
{
  //cout << "Parsing selection...";
	this->tokenizer.checkpoint();
	bool ret =  this->tokenizer.consume_Token("select")
	         && this->tokenizer.consume_Token("(")
	         && this->parse_Condition()
	         && this->tokenizer.consume_Token(")")
           && this->parse_Atomic();

	if(ret) {
   // cout << "Selection parsed." << endl;
	  //going to need stuff from condition and parse atomic, i assume	
	}
	else {
		this->tokenizer.back_Up();
    //cout << "Selection parse fail.\n";
	}
	return ret;
}

bool Parser::parse_Projection()
{
	//cout <<"Parsing projection...";
	this->tokenizer.checkpoint();
	bool ret = this->tokenizer.consume_Token("project")
	        && this->tokenizer.consume_Token("(")
	        && this->parse_Attribute_List()
	        && this->tokenizer.consume_Token(")")
          && this->parse_Atomic();
	if(ret) {
   //cout << "Projection parsed.\n\n";
	}
	else {
		this->tokenizer.back_Up();
		//cout << "Projection parse failed.\n\n";
	}
	return ret;
}

bool Parser::parse_Renaming()
{
	this->tokenizer.checkpoint();
	bool ret = this->tokenizer.consume_Token("RENAME")
	        && this->tokenizer.consume_Token("(")
	        && this->parse_Attribute_List()
	        && this->tokenizer.consume_Token(")")
          && this->parse_Atomic();

	if(ret) {
    //cout << "Renaming parsed.\n";
	}
	else {
		this->tokenizer.back_Up();
		//cout << "Renaming parse failed.\n";
	}
	return ret;
}

bool Parser::parse_Union()
{
	this->tokenizer.checkpoint();
	bool ret = this->parse_Atomic()
	        && this->tokenizer.consume_Token("+")
	        && this->parse_Atomic();

	if(ret) {
	  //cout << "Union parsed.\n";
	}
	else {
		this->tokenizer.back_Up();
		//cout << "Union parse failed.\n";
	}
	return ret;
}

bool Parser::parse_Difference()
{
	this->tokenizer.checkpoint();
	bool ret = this->parse_Atomic()
	        && this->tokenizer.consume_Token("-")
	        && this->parse_Atomic();

	if(ret) {
    //cout << "Difference parsed.\n";
	}
	else {
		this->tokenizer.back_Up();
	}
	return ret;
}

bool Parser::parse_Product()
{
	this->tokenizer.checkpoint();
	bool ret = this->parse_Atomic()
	        && this->tokenizer.consume_Token("*")
	        && this->parse_Atomic();

	if(ret) {
    //cout << "Product parsed.\n";
	}
	else {
		this->tokenizer.back_Up();
	}
	return ret;
}

bool Parser::parse_Condition()
{
	this->tokenizer.checkpoint();
	bool ret = this->parse_Conjunction();

	while (this->tokenizer.consume_Token( "||")) {
    ret &= this->parse_Conjunction();
  }

	if(ret) {
	  //cout << "Condition parsed.\n";
	}
	else {
	    this->tokenizer.back_Up();
	}
	return ret;
}

// not working
bool Parser::parse_Conjunction()
{
	this->tokenizer.checkpoint();
	bool ret = parse_Comparison();

	while(tokenizer.consume_Token("&&")) {
    ret &= parse_Comparison();
  }

	if(ret){
    //cout << "Conjunction parsed.\n";
	}
	else {
    this->tokenizer.back_Up();
  }
	return ret;
}

bool Parser::parse_Comparison()
{
  this->tokenizer.checkpoint();
  string op = "";
  string operand1 = "", operand2 = "";
  bool ret =((operand1 = this->parse_Literal()) != "")
    && ((op = this->parse_Op()) != "")
		&& ((operand2 = this->parse_Literal()) != "")
		|| this->tokenizer.consume_Token("(")
		&& this->parse_Condition()
		&& this->tokenizer.consume_Token(")");
		
  if(ret){
    //cout<<"Comparison parsed.\n";
  }
  else {
    tokenizer.back_Up();
  }
  return ret;
}

string Parser::parse_Op()
{
  tokenizer.checkpoint();
  string op = "";
  bool ret = false;
  op = parse_Literal();
  if (op ==  "=="
	 || op == "!="
	 || op == "<"
	 || op == ">"
	 || op == "<="
	 || op == ">="
	 || op == "") {
	   ret = true;
  }
  if (ret){
    //cout<<"Comparison parsed.\n";
  }
  else {
    this->tokenizer.back_Up();
  }
  return op;
}

//-------------------//
//--COMMAND PARSING--//
//-------------------//
bool Parser::parse_Command()
{
	return (this->parse_Open()
	     || this->parse_Close()
	     || this->parse_Write()
	     || this->parse_Exit()
	     || this->parse_Show()
	     || this->parse_Create()
	     || this->parse_Update()
	     || this->parse_Insert()
	     || this->parse_Delete() )
       && this->tokenizer.consume_Token(";");
}

bool Parser::parse_Open()
{
	this->tokenizer.checkpoint();
	string name = "";

	bool ret = this->tokenizer.consume_Token("OPEN")
		      && ((name = this->parse_Relation()) != "");
	if(ret) {
		//cout<<"Open parsed.\n";
		db->open(name);
	}
	else {
    this->tokenizer.back_Up();
  }
	return ret;
}

bool Parser::parse_Close()
{
 //cout << "Parsing close...";
	this->tokenizer.checkpoint();
	string name = "";

	bool ret = this->tokenizer.consume_Token("CLOSE")
		      && ((name = this->parse_Relation()) != "");

	if(ret) {
    //cout << "Close parsed.\n";
    db->close();
	}
	else {
    this->tokenizer.back_Up();
  }
	return ret;
}

bool Parser::parse_Write()
{
	this->tokenizer.checkpoint();
	string name = "";

	bool ret = this->tokenizer.consume_Token("WRITE")
		      && ((name = this->parse_Relation()) != "");

	if(ret) {
    //cout << "Write parsed.\n";
	}
	else {
    this->tokenizer.back_Up();
  }
	return ret;
}

bool Parser::parse_Exit()
{
	this->tokenizer.checkpoint();
	string name = "";

	bool ret = this->tokenizer.consume_Token("EXIT");

	if(ret){
    //cout << "Exit parsed.\n";
	}
	else {
    this->tokenizer.back_Up();
  }
	return ret;
}

bool Parser::parse_Show()
{
	this->tokenizer.checkpoint();
	string name = "";

	bool ret = this->tokenizer.consume_Token("SHOW")
		      && this->parse_Atomic();
	if(ret) {
    //cout << "Show parsed.\n";
	}
	else {
    this->tokenizer.back_Up();
  }
	return ret;
}

bool Parser::parse_Create()
{
	this->tokenizer.checkpoint();
	string name = "";

	bool ret = this->tokenizer.consume_Token("CREATE TABLE")
	        && (name = this->parse_Relation()) != ""
	        && this->tokenizer.consume_Token("(")
	        && this->parse_Typed_Attribute_List()
	        && this->tokenizer.consume_Token(")")
          && this->tokenizer.consume_Token("PRIMARY KEY")
          && this->tokenizer.consume_Token("(")
	        && this->parse_Attribute_List()
          && this->tokenizer.consume_Token(")");
	if(ret) {
	  //execute db engine calls
		//cout<<"Create Table parsed.\n";	
	}
	else {
		this->tokenizer.back_Up();
	}
	return ret;
}

bool Parser::parse_Update()
{
	this->tokenizer.checkpoint();
	string name = "";		//I used this variable for the attribute names too.
	//this will be changed when we have decide upon a good way of handling 
	//return values.

	bool ret = this->tokenizer.consume_Token("UPDATE")
		      && ((name = this->parse_Relation()) != "")
		      && tokenizer.consume_Token("SET")
		//there must be at least one attribute to set
	        && ((name = this->parse_Attribute_Name()) != "")
		      && this->tokenizer.consume_Token("==")
		      && ((name = this->parse_Literal()) != "");
		
		//only parse further if there are more comma sparated attributes to parse
while(tokenizer.consume_Token(",")) {
  ret = ret
     && ((name = this->parse_Attribute_Name()) != "")
     && this->tokenizer.consume_Token("==")
     && ((name = this->parse_Literal()) != "");
}

	if(ret) {
		//do some stuff
		//cout<<"Update parsed.\n";
	}
	else {
    this->tokenizer.back_Up();
  }
	return ret;
}

bool Parser::parse_Insert()
{
	this->tokenizer.checkpoint();
	string name = "";

	bool ret = this->tokenizer.consume_Token("INSERT INTO")
		      && ((name = this->parse_Relation()) != "")
		      && this->tokenizer.consume_Token("VALUES FROM")
		      && this->tokenizer.consume_Token("(")
		      && ((name = this->parse_Literal()) != "");
	
	while(this->tokenizer.consume_Token(",")) {
    ret &=((name = this->parse_Literal()) != "");
  }

	ret = ret
		|| this->tokenizer.consume_Token("INSERT INTO")
		&& ((name = this->parse_Relation()) != "")
		&& this->tokenizer.consume_Token("VALUES FROM RELATION")
		&& this->parse_Expr();

	if(ret) {
    //cout << "Insert parsed.\n";
	}
	else {
    this->tokenizer.back_Up();
  }
	return ret;
}

bool Parser::parse_Delete()
{
	this->tokenizer.checkpoint();
	string name = "";

	bool ret = this->tokenizer.consume_Token("DELETE FROM")
		      && ((name = this->parse_Relation()) != "")
		      && this->tokenizer.consume_Token("WHERE")
		      && this->parse_Condition();

	if(ret) {
    //cout << "Delete parsed.\n";
	}
	else tokenizer.back_Up();
	return ret;
}

string Parser::parse_Attribute_Name()
{
  string s = "";

  if(this->isid(this->tokenizer.get_Token())) {
    s = this->tokenizer.get_Token();
  	this->tokenizer.increase_Index();
  }
  return s;
}


bool Parser::parse_Attribute_List()
{
	this->tokenizer.checkpoint();
  bool ret;
  string s;
  this->attributes = vector<string>(); // initialize empty list
 
  s = this->parse_Attribute_Name();
  if(s != "") { // attribute name parse succeeded
    ret = true;
	  //cout<<"Attribute list parsed.\n";
  }
  else {
    this->tokenizer.back_Up();
  }
  while(s != "") { // consume list and store in attributes
    this->attributes.push_back(s);
    this->tokenizer.consume_Token(",");
    s = this->parse_Attribute_Name();
  }
  return ret;
}

// sets attributes to the value of the attribute list
bool Parser::parse_Typed_Attribute_List()
{ // this is broken, not parsing types...
	string name;
 	this->tokenizer.checkpoint();

  this->parse_Attribute_Name();

  bool ret = this->parse_Type();
  bool loop = ret;
  
  if(ret){
    //cout<<"typed attribute list parsed.\n";
  }
  else {
    this->tokenizer.back_Up();
  } 

  while(loop) {
    loop = this->tokenizer.consume_Token(",")
        && (this->parse_Attribute_Name() != "")
        && this->parse_Type();
  }
  return ret;  
}

bool Parser::parse_Type()
{
	this->tokenizer.checkpoint();
	bool ret = this->parse_Int_Type()
          || this->parse_Var_Type();

	if(ret){
		//do some stuff like  Type t = Type();
	}
	else {
    this->tokenizer.back_Up();
  }
	return ret;
}

bool Parser::parse_Var_Type()
{
  this->tokenizer.checkpoint();
  bool ret;

  ret = this->tokenizer.consume_Token("VARCHAR")
     && this->tokenizer.consume_Token("(")
     && this->parse_Int()
     && this->tokenizer.consume_Token(")");

  if(!ret) {
    tokenizer.back_Up();
  }
  return ret;
}

bool Parser::parse_Int_Type()
{
	this->tokenizer.checkpoint();
	string s;

	bool ret = this->tokenizer.consume_Token("INTEGER");	

	if (ret) {
	}
	else {
    this->tokenizer.back_Up();
  }
	return ret;
}

bool Parser::parse_Int()
{
  string s = tokenizer.get_Token();
  bool ret = s.find_first_not_of("0123456789") == std::string::npos; // this fragment lifted from Stack Overflow checks if is integer

  if(ret) {
    this->tokenizer.increase_Index();
  }
  return ret;
}

string Parser::parse_Literal()
{
	bool ret = false;
	string s = this->tokenizer.get_Token();

	this->tokenizer.increase_Index();
	//cout<<"Literal parsed.\n";
	return s;
}

//--------------------//
//--HELPER FUNCTIONS--//
//--------------------//

// returns true if the string is an alpha followed by 0 or more alphanumerics
bool Parser::isid(string id)
{
  return true;
  bool ret = false;
  if(isalpha(id[0])) {
    ret = true;
  }
  for(char c: id) {
    if(isalnum(c)) {
      ret = true;
    }
  }
  return ret;
}