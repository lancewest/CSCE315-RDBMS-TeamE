#include "Token.h"

Token::Token(string v, string k) : value(v), kind(k) {}

string Token::get_Value()
{
  return this->value;
}

string Token::get_Kind()
{
  return this->kind;
}

void Token::set_Kind(string new_kind)
{
  this->kind = new_kind;
}