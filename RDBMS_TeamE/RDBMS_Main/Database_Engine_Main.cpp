#include <vector>
#include <string>
#include <iostream>

#include "DB_Engine.h"

using namespace std;

int main()
{
  //Main output crude, early implementation of show()

  DB_Engine *engine = new DB_Engine();

  Attribute *client_id = new Attribute(1, true, "Client Id");
  Attribute *client_name = new Attribute("Lance West", false, "Client Name", 1);
  vector<Attribute> tuple_attributes;
  tuple_attributes.push_back(*client_id);
  tuple_attributes.push_back(*client_name);
  Tuple *tuple = new Tuple(tuple_attributes);

  Attribute *client_id2 = new Attribute(123, true, "Client Id");
  Attribute *client_name2 = new Attribute("Iron Man", false, "Client Name", 1);
  vector<Attribute> tuple_attributes2;
  tuple_attributes2.push_back(*client_id2);
  tuple_attributes2.push_back(*client_name2);
  Tuple *tuple2 = new Tuple(tuple_attributes2);

  Attribute *client_id3 = new Attribute(55, true, "Client Id");
  Attribute *client_name3 = new Attribute("Billy Bob", false, "Client Name", 1);
  vector<Attribute> tuple_attributes3;
  tuple_attributes3.push_back(*client_id3);
  tuple_attributes3.push_back(*client_name3);
  Tuple *tuple3 = new Tuple(tuple_attributes3);

  engine->create_Table("Clients");

  engine->insert( *(engine->get_Table("Clients")), *tuple);
  engine->insert( *(engine->get_Table("Clients")), *tuple2);
  engine->insert( *(engine->get_Table("Clients")), *tuple3);

  engine->show(*(engine->get_Table("Clients")));

  cout << "\n\n\nEnter any character to terminate program: \n";
  char c;
  cin >> c;
}



