#include "Tokenizer.h"
#include <iostream>

Tokenizer::Tokenizer(){}

void Tokenizer::checkpoint()
{
  this->point = this->index;
}

void Tokenizer::back_Up()
{
  this->index = this->point;
}

bool Tokenizer::consume_Token(string in)
{
  if(this->index == this->tokens.size()) {
    return false;
  }
  if(in == tokens[index]) {
    index++;
    return true;
  }
  return false;
}

string Tokenizer::get_Token()
{
  if(this->index == this->tokens.size()) {
    return "";
  }

  return tokens[index];
}

Tokenizer::Tokenizer(string* text) : position(0), index(0), point(0)
{
  vector<string> possible_tokens;
    possible_tokens.push_back("OPEN");
    possible_tokens.push_back("CLOSE");
    possible_tokens.push_back("WRITE");
    possible_tokens.push_back("EXIT");
    possible_tokens.push_back("SHOW");
    possible_tokens.push_back("CREATE TABLE");
    possible_tokens.push_back("PRIMARY KEY");
    possible_tokens.push_back("UPDATE");
    possible_tokens.push_back("SET");
    possible_tokens.push_back("WHERE"); 
    possible_tokens.push_back("INSERT INTO");
    possible_tokens.push_back("VALUES FROM RELATION");
    possible_tokens.push_back("VALUES FROM");
    possible_tokens.push_back("select");
    possible_tokens.push_back("project");
    possible_tokens.push_back("join");
    possible_tokens.push_back("RENAME");
    possible_tokens.push_back("DELETE FROM");
    possible_tokens.push_back("VARCHAR");
    possible_tokens.push_back("INTEGER");
  //operators
    possible_tokens.push_back("==");
    possible_tokens.push_back("<-");
    possible_tokens.push_back("!=");
    possible_tokens.push_back("<=");
    possible_tokens.push_back(">=");
    possible_tokens.push_back("<");
    possible_tokens.push_back(">");
    possible_tokens.push_back("+");
    possible_tokens.push_back("-");
    possible_tokens.push_back("*");
    possible_tokens.push_back("(");
    possible_tokens.push_back(")");
    possible_tokens.push_back("||"); 
    possible_tokens.push_back(",");
    possible_tokens.push_back("&&");
    possible_tokens.push_back("\"");
    possible_tokens.push_back(";");
  //literals: VARCHAR INTEGER

  while(this->position < text->size()) {
    bool found_command = false;
    for(string& i: possible_tokens) {

      if(this->match(text, position, i)) {
        this->tokens.push_back(i);

        this->position += i.size();
      
        found_command = true;
        break;
      }
    }
    if(found_command == true) {
      continue;
    }
    char c = (*text)[position];

    if(isdigit(c)) {
      string temp = this->get_Integer(text, position);
      this->tokens.push_back(temp);
      this->position += temp.size();
      continue;
    }

    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c == '_')) {
      string temp = this->get_Varchar(text, position);
      this->tokens.push_back(temp);
      this->position += temp.size();
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
  this->index =+ addend;
}