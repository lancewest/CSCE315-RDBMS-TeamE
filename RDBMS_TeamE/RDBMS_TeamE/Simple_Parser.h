#pragma once

#include "parser.h"
#include "Tokenizer.h"
#include "DB_Engine.h"
#include <iostream>
#include <vector>
#include <string>
#include <stdlib.h>

using namespace std;

class Simple_Parser {
private:
  DB_Engine db;
public:
  Simple_Parser();

  // This simple parser integrates with the dbEngine and provides necessary core functions for building our application
	bool parse(string input);
  
  // assume that there is only one attribute involved... may fix this later
  vector<Attribute> get_Attributes(string input);
};