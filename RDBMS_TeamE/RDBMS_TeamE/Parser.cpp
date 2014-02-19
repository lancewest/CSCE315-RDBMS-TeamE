#include "Parser.h"
#include <iostream>

using namespace std;

//constructor
Parser::Parser(DB_Engine* db_ptr, string c) : db(db_ptr), command(c), tokenizer(&c) {}

bool Parser::parse()
{
  if(this->tokenizer.get_Token().get_Kind() == "command") {
    return parse_Command();
  }

  Token operand_relation_name = this->tokenizer.get_Token();
	if(operand_relation_name.get_Kind() == "relation name") {
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

    if(this->tokenizer.consume_Token("OPEN") ) {
       Token relation_name = this->tokenizer.get_Token();
       if(relation_name.get_Kind() == "relation name")

         this->tokenizer.increase_Index();
         db->open(relation_name.get_Value());
         return true;
    }
  }

  //CLOSE
  if(this->tokenizer.get_Token().get_Value() == "CLOSE") {

    if(this->tokenizer.consume_Token("CLOSE") ) {
       Token relation_name = this->tokenizer.get_Token();
       if(relation_name.get_Kind() == "relation name")

         this->tokenizer.increase_Index();
         db->close(relation_name.get_Value());
         return true;
    }
  }

  //WRITE
  if(this->tokenizer.get_Token().get_Value() == "WRITE") {

    if( this->tokenizer.consume_Token("WRITE") ) {
      Token name = this->tokenizer.get_Token();
      if(name.get_Kind() == "relation name") {
        this->tokenizer.increase_Index();
        db->write( *(db->get_Table(name.get_Value())) );
        return true;
      }
    }
  }

  //SHOW
  if(this->tokenizer.get_Token().get_Value() == "SHOW") {

    if(this->tokenizer.consume_Token("SHOW") ) {
       Token relation_name = this->tokenizer.get_Token();
       if(relation_name.get_Kind() == "relation name")

         this->tokenizer.increase_Index();
       db->show( *(db->get_Table(relation_name.get_Value())) );
         return true;
    }
  }

  //UPDATE
  if(this->tokenizer.get_Token().get_Value() == "UPDATE") {

    if(this->tokenizer.consume_Token("UPDATE") ) {
      Token relation_name = this->tokenizer.get_Token();
      if(relation_name.get_Kind() == "relation name") {
        this->tokenizer.increase_Index();

        if(this->tokenizer.consume_Token("SET") ) {
          pair< bool, vector<pair<string,string>> > assignments = this->parse_Assignment_List();

          if(this->tokenizer.consume_Token("WHERE") ) {
            pair<bool,vector<Condition>> conditions = this->parse_Condition_List();
            if(conditions.first)
            {
              db->update( *(db->get_Table(relation_name.get_Value())), assignments.second, conditions.second);
              return true;
            }
          }
        }
      }
    }

    return false;
  }

  //CREATE TABLE
  if(this->tokenizer.get_Token().get_Value() == "CREATE TABLE") {

    if(this->tokenizer.consume_Token("CREATE TABLE") ) {

      Token name = this->tokenizer.get_Token();
      if(name.get_Kind() == "relation name") {
        this->tokenizer.increase_Index();

        pair<bool,Tuple> attributes = this->parse_Typed_Attribute_List();
        if(attributes.first) {

          if( this->tokenizer.consume_Token("PRIMARY KEY") ) {
                
            pair<bool,vector<string>> primes = this->parse_Attribute_List();

            for(Attribute a : attributes.second.get_Attributes()) {
              for(string prime : primes.second) {
                if(a.get_Name() == prime)
                  a.set_Is_Primary(true);
              }
            }

            if(primes.first) {
              db->create_Table(name.get_Value(), attributes.second);
              return true;
             }
           }
         }
       }
    }
  }

  //INSERT INTO
  if(this->tokenizer.get_Token().get_Value() == "INSERT INTO") {

    if(this->tokenizer.consume_Token("INSERT INTO") ) {
      Token relation_name = this->tokenizer.get_Token();

      if(relation_name.get_Kind() == "relation name") {
        this->tokenizer.increase_Index();

        if(this->tokenizer.consume_Token("VALUES FROM") ) {
          pair<bool,vector<Attribute>> literals = this->parse_Literal_List();

          Tuple template_tuple = db->get_Table(relation_name.get_Value())->get_Template_Tuple();
          if(literals.second.size() != template_tuple.get_Size())
            return false;

          for(int i = 0; i<literals.second.size() ; i++) {
            literals.second[i].set_Is_Primary( template_tuple.get_Attributes()[i].is_Primary() );
            literals.second[i].set_Name( template_tuple.get_Attributes()[i].get_Name() );
            literals.second[i].set_Length( template_tuple.get_Attributes()[i].get_Length() );
          }

          db->insert( *(db->get_Table(relation_name.get_Value())), Tuple(literals.second) );
          return true;
        }

         if(this->tokenizer.consume_Token("VALUES FROM RELATION") &&
            this->parse_Expression()) {
              return true;
         }
      }
    }
  }

  //DELETE FROM
  if(this->tokenizer.get_Token().get_Value() == "DELETE FROM") {

    if(this->tokenizer.consume_Token("DELETE FROM") &&
       this->tokenizer.get_Token().get_Kind() == "relation name") {

         this->tokenizer.increase_Index();

         if(this->tokenizer.consume_Token("WHERE") &&
           this->parse_Condition_List().first) {
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
       this->parse_Condition_List().first) {

         if(this->parse_Expression()) {
               return true;
         }
    }
  }

  //project
  if(this->tokenizer.get_Token().get_Value() == "project") {

    if(this->tokenizer.consume_Token("project") &&
       this->parse_Attribute_List().first) {

         if(this->parse_Expression()) {
           return true;
         }
    }
  }

  //rename
  if(this->tokenizer.get_Token().get_Value() == "rename") {
    if(this->tokenizer.consume_Token("rename") &&
       this->parse_Attribute_List().first) {

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

/*bool Parser::parse_Condition()
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
}*/

pair<bool, vector<Condition>> Parser::parse_Condition_List()
{
  //While loop that reads in an attribute, operator, value, and possibly a conjunction all at the same time to make list of conditions

  this->tokenizer.consume_Token("(");
  vector<Condition> conditions = vector<Condition>();
  Token conditional_attribute = this->tokenizer.get_Token();
  tokenizer.increase_Index();
  Token compare_operator = this->tokenizer.get_Token();
  tokenizer.increase_Index();
  Token value = this->tokenizer.get_Token();
  tokenizer.increase_Index();
  Token conjunction = this->tokenizer.get_Token();
  tokenizer.increase_Index();

  while(conjunction.get_Value() != ";") {

    if(conditional_attribute.get_Kind() == "relation name" 
        || compare_operator.get_Kind() == "condition operator" 
        || conjunction.get_Kind() == "conjunction") {

      return pair<bool, vector<Condition>>(false,vector<Condition>());
    }

    conditions.push_back( Condition(conditional_attribute.get_Value(), compare_operator.get_Value(), value.get_Value(), conjunction.get_Value()) );

    conditional_attribute = this->tokenizer.get_Token();
    tokenizer.increase_Index();
    compare_operator = this->tokenizer.get_Token();
    tokenizer.increase_Index();
    value = this->tokenizer.get_Token();
    tokenizer.increase_Index();
    conjunction = this->tokenizer.get_Token();
    tokenizer.increase_Index();
  }

  return pair<bool, vector<Condition>>(true, conditions);
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

pair< bool, vector<pair<string,string>> > Parser::parse_Assignment_List()
{
  this->tokenizer.consume_Token("(");

  vector<pair<string,string>> assignments = vector<pair<string,string>>();
  pair<bool, pair<string,string>> assignment = this->parse_Assignment();

  while(assignment.first) {
    assignments.push_back(assignment.second);
    if(this->tokenizer.consume_Token(",")) {
      assignment = this->parse_Assignment();
      continue;
    }
    break;
  }

  this->tokenizer.consume_Token(")");
  return pair< bool, vector<pair<string,string>> >( true, assignments );

  return pair< bool, vector<pair<string,string>> >( false, assignments );
}

pair<bool, pair<string,string>> Parser::parse_Assignment()
{
	Token attribute_name = tokenizer.get_Token();
  if(attribute_name.get_Kind() == "relation name") {
    this->tokenizer.increase_Index();

    if(tokenizer.consume_Token("=")) {
      pair<bool,Attribute> lit = this->parse_Literal();

      string value = lit.second.is_Int() ? to_string(lit.second.get_Int_Value()) : lit.second.get_String_Value();

      if(lit.first) {
        return pair<bool, pair<string,string>>( true, pair<string,string>(attribute_name.get_Value(), value) );
      }
      
    }
  }
  return pair<bool, pair<string,string>>( false, pair<string,string>("","") );
}

pair<bool, Attribute> Parser::parse_Typed_Attribute()
{
	Token name = tokenizer.get_Token();
  if(name.get_Kind() == "relation name") {
    this->tokenizer.increase_Index();

    if(this->tokenizer.consume_Token("INTEGER")) {
	  Attribute a = Attribute(-1,false,name.get_Value());
      return pair<bool, Attribute>(true,a);
    }
    else if(this->tokenizer.consume_Token("VARCHAR") && this->tokenizer.consume_Token("(") ) {

      Token length = this->tokenizer.get_Token() ;
      if(length.get_Kind() == "digit") {
        Attribute a = Attribute( "dummy_value",false,name.get_Value(), atoi(length.get_Value().c_str()) );
        this->tokenizer.increase_Index();

        if(this->tokenizer.consume_Token(")")) {
          return pair<bool, Attribute>(true,a);
        }
      }
    }
  }
  return pair<bool, Attribute>(false,Attribute(-1,false,"emtpy"));
}

pair<bool,Tuple> Parser::parse_Typed_Attribute_List()
{
  if(this->tokenizer.consume_Token("(")) {
    vector<Attribute> attributes = vector<Attribute>();
    pair<bool,Attribute> attribute = this->parse_Typed_Attribute();
    while(attribute.first) {
      attributes.push_back(attribute.second);
      if(this->tokenizer.consume_Token(",")) {
        attribute = this->parse_Typed_Attribute();
        continue;
      }
      break;
    }

    if(this->tokenizer.consume_Token(")")) {
      return pair<bool,Tuple>( true, Tuple(attributes) );
    }
  }

  return pair<bool,Tuple>( false, Tuple() );
}

pair<bool,string> Parser::parse_Attribute()
{
  Token name = this->tokenizer.get_Token();
  if(name.get_Kind() == "relation name") {
    this->tokenizer.increase_Index();
    return pair<bool,string>(true, name.get_Value());
  }
  return pair<bool,string>();
}

pair<bool, vector<string>> Parser::parse_Attribute_List()
{
  if(this->tokenizer.consume_Token("(")) {
    vector<string> attributes = vector<string>();
    pair<bool,string> attribute = this->parse_Attribute();
    while(attribute.first) {
      if(this->tokenizer.consume_Token(",")) {
        attributes.push_back(attribute.second);
        attribute = this->parse_Attribute();
        continue;
      }
      break;
    }

    if(this->tokenizer.consume_Token(")")) {
      return pair<bool,vector<string>>( true, attributes);
    }
  }

  return pair<bool,vector<string>>(false, vector<string>());
}

pair<bool,Attribute> Parser::parse_Literal()
{
  Token lit = this->tokenizer.get_Token();
  if(lit.get_Kind() == "digit") {
    Attribute* a = new Attribute( atoi(lit.get_Value().c_str()), false, "Temp");
    this->tokenizer.increase_Index();
    return pair<bool,Attribute>(true, *a);
  }

  if(this->tokenizer.consume_Token("\"") ) {
    Token lit = this->tokenizer.get_Token();
    if(lit.get_Kind() == "relation name") {
      this->tokenizer.increase_Index();
      if(this->tokenizer.consume_Token("\"")) {
        return pair<bool,Attribute>(true, Attribute(lit.get_Value(), false, "Temp", 1) );
       }
    }
  }
  
  return pair<bool,Attribute>(true, Attribute(-1,false,"empty"));
}

pair<bool,vector<Attribute>> Parser::parse_Literal_List()
{
  vector<Attribute> attributes = vector<Attribute>();

  if(this->tokenizer.consume_Token("(")) {

    pair<bool,Attribute> lit = this->parse_Literal();
    while(lit.first) {
      attributes.push_back(lit.second);

      if(this->tokenizer.consume_Token(",")) {
        lit = this->parse_Literal();
        continue;
      }
      break;
    }

    if(this->tokenizer.consume_Token(")")) {
      return pair<bool,vector<Attribute>>(true,attributes);
    }
  }

  return pair<bool,vector<Attribute>>(false,vector<Attribute>());
}