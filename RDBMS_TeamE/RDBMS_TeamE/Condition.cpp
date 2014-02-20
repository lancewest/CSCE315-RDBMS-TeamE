#include "Condition.h"

using namespace std;

Condition::Condition(string a, string c, string v, string con, bool l) : attribute(a), compare_operator(c), value(v), conjunction(con), is_literal(l) { }