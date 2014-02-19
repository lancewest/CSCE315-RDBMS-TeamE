// Patrick Rock
// 9/3/2013
// Testing file for database engine

#include <fstream>
#include <iostream>
#include "table.h"
#include "DB_Engine.h"
#include <vector>
#include "Tokenizer.h"
#include "parser.h"
#include "Simple_Parser.h"
#include "Condition.h"

bool f(Attribute a) {
	return true;
}

int main() {
  //Read in from file
  DB_Engine db;

  cout << "\n\n\nSQL from file test\n========================\n";
  db.open("sql.txt");

  cout << "Enter any character to terminate program.\n";
  char c;
  cin >> c;
}