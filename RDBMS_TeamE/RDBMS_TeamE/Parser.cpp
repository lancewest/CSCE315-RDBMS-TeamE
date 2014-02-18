#include "Parser.h"
#include <iostream>

using namespace std;

//constructor
Parser::Parser(string c) : command(c), tokenizer(&c) {}

bool Parser::parse()
{
  if(this->tokenizer.get_Token().get_Kind() == "command") {
    return parse_Command();
  }

	else if(this->tokenizer.get_Token().get_Kind() == "relation name") {
    this->tokenizer.increase_Index();
    if(this->tokenizer.get_Token().get_Kind() == "query operator") {
      this->tokenizer.increase_Index();
      return parse_Query();
    }
  }

  else if(this->tokenizer.consume_Token(";")) {
    return true;
  }

  return false;
}

bool Parser::parse_Command()
{
  //OPEN
  if(this->tokenizer.get_Token().get_Value() == "OPEN") {

    if(this->tokenizer.consume_Token("OPEN") &&
       this->tokenizer.get_Token().get_Kind() == "relation name") {

         this->tokenizer.increase_Index();
         return true;
    }
  }

  //CLOSE
  if(this->tokenizer.get_Token().get_Value() == "CLOSE") {

    if(this->tokenizer.consume_Token("CLOSE") &&
       this->tokenizer.get_Token().get_Kind() == "relation name") {

         this->tokenizer.increase_Index();
         return true;
    }
  }

  //WRITE
  if(this->tokenizer.get_Token().get_Value() == "WRITE") {

    if(this->tokenizer.consume_Token("WRITE") &&
       this->tokenizer.get_Token().get_Kind() == "relation name") {

         this->tokenizer.increase_Index();
         return true;
    }
  }

  //EXIT
  if(this->tokenizer.get_Token().get_Value() == "EXIT") {
      this->tokenizer.consume_Token("EXIT");
      return true;
  }

  //SHOW
  if(this->tokenizer.get_Token().get_Value() == "SHOW") {

    if(this->tokenizer.consume_Token("SHOW") &&
       this->tokenizer.get_Token().get_Kind() == "relation name") {

         this->tokenizer.increase_Index();
         return true;
    }
  }

  //UPDATE
  if(this->tokenizer.get_Token().get_Value() == "UPDATE") {

    if(this->tokenizer.consume_Token("UPDATE") &&
       this->tokenizer.get_Token().get_Kind() == "relation name") {

         this->tokenizer.increase_Index();

         if(this->tokenizer.consume_Token("SET") &&
            this->parse_Assignment()) {

              if(this->tokenizer.consume_Token("WHERE") &&
                 this->parse_Condition()) {
                   return true;
             }
         }
    }
  }

  //CREATE TABLE
  if(this->tokenizer.get_Token().get_Value() == "CREATE TABLE") {

    if(this->tokenizer.consume_Token("CREATE TABLE") &&
       this->tokenizer.get_Token().get_Kind() == "relation name") {

         this->tokenizer.increase_Index();

         if(this->parse_Typed_Attribute_List()) {

              if(this->tokenizer.consume_Token("PRIMARY KEY") &&
                 this->parse_Attribute_List()) {
                   return true;
             }
         }
    }
  }

  //INSERT INTO
  if(this->tokenizer.get_Token().get_Value() == "INSERT INTO") {

    if(this->tokenizer.consume_Token("INSERT INTO") &&
       this->tokenizer.get_Token().get_Kind() == "relation name") {

         this->tokenizer.increase_Index();

         if(this->tokenizer.consume_Token("VALUES FROM") &&
            this->parse_Literal_List()) {
              return true;
         }

         if(this->tokenizer.consume_Token("VALUES FROM RELATION") &&
            this->parse_Expression()) {
              return true;
         }
     }
  }

  //DELETE FROM
  if(this->tokenizer.get_Token().get_Value() == "DELETE FROM") {

    if(this->tokenizer.consume_Token("DELETE FROM") &&
       this->tokenizer.get_Token().get_Kind() == "relation name") {

         this->tokenizer.increase_Index();

         if(this->tokenizer.consume_Token("WHERE") &&
            this->parse_Condition()) {
               return true;
         }
    }
  }

  return false;
}

bool Parser::parse_Query()
{
  //select
  if(this->tokenizer.get_Token().get_Value() == "select") {

    if(this->tokenizer.consume_Token("select") &&
       this->parse_Condition_List()) {

         if(this->parse_Expression()) {
               return true;
         }
    }
  }

  //project
  if(this->tokenizer.get_Token().get_Value() == "project") {

    if(this->tokenizer.consume_Token("project") &&
       this->parse_Attribute_List()) {

         if(this->parse_Expression()) {
           return true;
         }
    }
  }

  //rename
  if(this->tokenizer.get_Token().get_Value() == "rename") {
    if(this->tokenizer.consume_Token("rename") &&
       this->parse_Attribute_List()) {

         if(this->parse_Expression()) {
           return true;
         }
    }
  }

   if(this->parse_Expression()) {

    //JOIN
    if(this->tokenizer.consume_Token("JOIN")) {
      return this->parse_Expression();
    }
    //*
    if(this->tokenizer.consume_Token("*")) {
      return this->parse_Expression();
    }
    //+
    if(this->tokenizer.consume_Token("+")) {
      return this->parse_Expression();
    }
    //-
    if(this->tokenizer.consume_Token("-")) {
      return this->parse_Expression();
    }
  }

  return this->parse_Expression();
}

bool Parser::parse_Condition()
{
    if(this->tokenizer.get_Token().get_Kind() == "relation name") {
      this->tokenizer.increase_Index();
    }
    else if(!this->parse_Literal()) {
      return false;
    }

    if(this->tokenizer.get_Token().get_Kind() == "condition operator") {
       this->tokenizer.increase_Index();

       if(this->tokenizer.get_Token().get_Kind() == "relation name") {
         this->tokenizer.increase_Index();
       }

       else if(!this->parse_Literal()) {
         return false;
       }
    }

  return true;
}

bool Parser::parse_Condition_List()
{
  if(this->tokenizer.consume_Token("(")) {
    while(this->parse_Condition()) {
      if(this->tokenizer.get_Token().get_Kind() == "conjunction") {
        this->tokenizer.increase_Index();
        continue;
      }
      break;
    }

    if(this->tokenizer.consume_Token(")")) {
      return true;
    }
  }
  return false;
}

bool Parser::parse_Expression()
{
  this->tokenizer.consume_Token("(");
  this->tokenizer.consume_Token(")");

  if(this->tokenizer.get_Token().get_Kind() == "relation name" ||
     this->tokenizer.get_Token().get_Kind() == "semicolon") {
    this->tokenizer.increase_Index();
    //this->tokenizer.consume_Token(")");
    return true;
  }

  else {
    return this->parse_Query();
  }

  return false;
}

bool Parser::parse_Assignment()
{
  return true;
  return false;
}

bool Parser::parse_Typed_Attribute()
{
  if(this->tokenizer.get_Token().get_Kind() == "relation name") {
    this->tokenizer.increase_Index();

    if(this->tokenizer.consume_Token("INTEGER")) {
      return true;
    }
    else if(this->tokenizer.consume_Token("VARCHAR") &&
            this->tokenizer.consume_Token("(") &&
            this->tokenizer.get_Token().get_Kind() == "digit") {
              this->tokenizer.increase_Index();

              if(this->tokenizer.consume_Token(")")) {
                return true;
              }
    }
  }
  return false;
}

bool Parser::parse_Typed_Attribute_List()
{
  if(this->tokenizer.consume_Token("(")) {
    while(this->parse_Typed_Attribute()) {
      if(this->tokenizer.consume_Token(",")) {
        continue;
      }
      break;
    }

    if(this->tokenizer.consume_Token(")")) {
      return true;
    }
  }

  return false;
}

bool Parser::parse_Attribute()
{
  if(this->tokenizer.get_Token().get_Kind() == "relation name") {
    this->tokenizer.increase_Index();
    return true;
  }
  return false;
}

bool Parser::parse_Attribute_List()
{
  if(this->tokenizer.consume_Token("(")) {
    while(this->parse_Attribute()) {
      if(this->tokenizer.consume_Token(",")) {
        continue;
      }
      break;
    }

    if(this->tokenizer.consume_Token(")")) {
      return true;
    }
  }

  return false;
}

bool Parser::parse_Literal()
{
  if(this->tokenizer.get_Token().get_Kind() == "digit") {
    this->tokenizer.increase_Index();
    return true;
  }

  else if(this->tokenizer.consume_Token("\"") &&
     this->tokenizer.get_Token().get_Kind() == "relation name") {
       this->tokenizer.increase_Index();
       if(this->tokenizer.consume_Token("\"")) {
         return true;
       }
  }
  
  return false;
}

bool Parser::parse_Literal_List()
{
  if(this->tokenizer.consume_Token("(")) {
    while(this->parse_Literal()) {
      if(this->tokenizer.consume_Token(",")) {
        continue;
      }
      break;
    }

    if(this->tokenizer.consume_Token(")")) {
      return true;
    }
  }

  return false;
}