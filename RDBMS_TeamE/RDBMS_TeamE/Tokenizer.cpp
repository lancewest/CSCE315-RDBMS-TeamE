#include "Tokenizer.h"
#include <iostream>

Tokenizer::Tokenizer(){}

//For Rolling back transactions
void Tokenizer::checkpoint() 
{
  this->point = this->index;
}

//Useing in conjunction with checkpoint to roll back
void Tokenizer::back_Up() 
{
  this->index = this->point;
}

bool Tokenizer::consume_Token(string in)
{
  if(this->index == this->tokens.size()) {
    return false;
  }
  if(in == tokens[index].get_Value()) {
    index++;
    return true;
  }
  return false;
}

//Return token without consuming
Token Tokenizer::get_Token()
{
  if(this->index == this->tokens.size()) {
    return Token("", "");
  }

  return tokens[index];
}

/*First step to parse a command, this breaks it into tokens (simply strings) and puts 
them in order in the tokenizer vector for the parse to parse from*/
Tokenizer::Tokenizer(string* text) : position(0), index(0), point(0)
{
  vector<Token> possible_tokens;
    possible_tokens.push_back(Token("OPEN", "command"));
    possible_tokens.push_back(Token("CLOSE", "command"));
    possible_tokens.push_back(Token("WRITE", "command"));
    possible_tokens.push_back(Token("EXIT", "command"));
    possible_tokens.push_back(Token("SHOW", "command"));
    possible_tokens.push_back(Token("CREATE TABLE", "command"));
    possible_tokens.push_back(Token("PRIMARY KEY", "keyword"));
    possible_tokens.push_back(Token("UPDATE", "command"));
    possible_tokens.push_back(Token("SET", "keyword"));
    possible_tokens.push_back(Token("WHERE", "keyword")); 
    possible_tokens.push_back(Token("INSERT INTO", "command"));
    possible_tokens.push_back(Token("VALUES FROM RELATION", "keyword"));
    possible_tokens.push_back(Token("VALUES FROM", "keyword"));
    possible_tokens.push_back(Token("select", "query"));
    possible_tokens.push_back(Token("project", "query"));;
    possible_tokens.push_back(Token("rename", "query"));
    possible_tokens.push_back(Token("DELETE FROM", "command"));
    possible_tokens.push_back(Token("VARCHAR", "literal"));
    possible_tokens.push_back(Token("INTEGER", "literal"));
  //operators
    possible_tokens.push_back(Token("==", "condition operator"));
    possible_tokens.push_back(Token("<-", "query operator"));
    possible_tokens.push_back(Token("!=", "condition operator"));
    possible_tokens.push_back(Token("<=", "condition operator"));
    possible_tokens.push_back(Token(">=", "condition operator"));
    possible_tokens.push_back(Token("<", "condition operator"));
    possible_tokens.push_back(Token(">", "condition operator"));
    possible_tokens.push_back(Token("+", "operator"));
    possible_tokens.push_back(Token("-", "operator"));
    possible_tokens.push_back(Token("JOIN", "operator"));
    possible_tokens.push_back(Token("*", "operator"));
    possible_tokens.push_back(Token("(", "opening parenthesis"));
    possible_tokens.push_back(Token(")", "closing parenthesis"));
    possible_tokens.push_back(Token("||", "conjunction")); 
    possible_tokens.push_back(Token(",", "comma"));
    possible_tokens.push_back(Token("&&", "conjunction"));
    possible_tokens.push_back(Token("\"", "quotes"));
    possible_tokens.push_back(Token(";", "semicolon"));
  //literals: VARCHAR INTEGER

  while(this->position < text->size()) {
    bool found_command = false;
    for(Token& i: possible_tokens) {

      if(this->match(text, position, i.get_Value())) {
        this->tokens.push_back(i);

        this->position += i.get_Value().size();
      
        found_command = true;
        break;
      }
    }
    if(found_command == true) {
      continue;
    }
    char c = (*text)[position];

    if(isdigit(c)) {
      Token temp(this->get_Integer(text, position), "digit");
      this->tokens.push_back(temp);
      this->position += temp.get_Value().size();
      continue;
    }

    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_')) {
      Token temp(this->get_Varchar(text, position), "relation name");
      this->tokens.push_back(temp);
      this->position += temp.get_Value().size();
      continue;
    }

    //ignore everything else
    else {
      position++;
      continue;
    }
  }
/*for(string& i: this->tokens) {
    cout << i << " ";
  }
*/
}

bool Tokenizer::match(string *text, int position, string exp)
{
  string substring = text->substr(position, exp.size());

  if (substring == exp) {
    return true;
  }

  return false;
}

string Tokenizer::get_Integer(string* text, int position)
{
  char c = (*text)[position];
  string integer;

  while(isdigit(c)) {
    integer.push_back(c);
    position++;
    c = (*text)[position];
  }

  return integer;
}

string Tokenizer::get_Varchar(string* text, int position)
{
  char c = (*text)[position];
  string varchar;

  while(isalnum(c) || (c == '_')) {
    varchar.push_back(c);
    position++;
    c = (*text)[position];
  }

  return varchar;
}

void Tokenizer::increase_Index(int addend)
{
  this->index += addend;
}

bool Tokenizer::is_One_Valid_Line()
{
  int count = 0;
  for(Token t : tokens) {
    if( (t.get_Kind() == "command" || t.get_Kind() == "query operator"))
      count++;
  }

  return count < 2;
}
