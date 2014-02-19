#include "Condition.h"

using namespace std;

Condition::Condition() : attribute(), compare_operator(), value(), conjunction() { }

Condition::Condition(string a, string c, string v, string con) : attribute(a), compare_operator(c), value(v), conjunction(con) { }