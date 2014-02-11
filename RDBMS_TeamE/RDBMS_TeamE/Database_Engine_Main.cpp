#include <vector>
#include <string>
#include <iostream>
#include "table.h"
#include "tuple.h"
//#include "record.h"
//#include "exception.h"

using namespace std;

/*Table* read_from_db2() 
{
 if (myfile.is_open())
  {
  
  Table::ColumnList columns;
  
    String accountID;
	getline( myfile, accountID, ',' );
    columns.push_back(make_pair(placeID, Table::integer));
	
	String name;
	getline( myfile, name, ',' );
    columns.push_back(make_pair(name, Table::varchar));
	
	String address;
	getline( myfile, address, ',' );
    columns.push_back(make_pair(address, Table::varchar));
	
	String city;
	getline( myfile, city, ',' );
    columns.push_back(make_pair(city, Table::varchar));

	String state;
	getline( myfile, state, ',' );
    columns.push_back(make_pair(state, Table::varchar));

	String country;
	getline( myfile, country, ',' );
    columns.push_back(make_pair(country, Table::varchar));
	
	String fax;
	getline( myfile, fax, ',' );
    columns.push_back(make_pair(fax, Table::varchar));

	String zip;
	getline( myfile, zip, ',' );
    columns.push_back(make_pair(zip, Table::varchar));
	
	String other_services;
	getline( myfile, other_services, '\n' );
    columns.push_back(make_pair(other_services, Table::varchar));
	
	Table* geo = new Table(columns); // Create geo using the defined columns
	
	    
	while ( myfile.good() )
    {
	  vector<pair<string, string> > entries; // Entries for the record to be placed in the table
	  
	  string AccountID;
	  getline( myfile, AccountID, ',' );
	  pair <string,string> pair0  ("placeID",placeID);   // value init
	  entries.push_back(pair0);

	  string name;
	  getline( myfile, name, ',' );
	  pair <string,string> pair1  ("name",name);   // value init
	  entries.push_back(pair1);

	  string address;
	  getline( myfile, address, ',' );
	  pair <string,string> pair2  ("address",address);   // value init
	  entries.push_back(pair2);

	  string city;
	  getline( myfile, city, ',' );
	  pair <string,string> pair3  ("city",city);   // value init
	  entries.push_back(pair3);

	  string state;
	  getline( myfile, state, ',' );
	  pair <string,string> pair4  ("state",state);   // value init
	  entries.push_back(pair4);

	  string country;
	  getline( myfile, country, ',' );
	  pair <string,string> pair5  ("country",country);   // value init
	  entries.push_back(pair5);

	  string fax;
	  getline( myfile, fax, ',' );
	  pair <string,string> pair6  ("fax",fax);   // value init
	  entries.push_back(pair6);

	  string zip;
	  getline( myfile, zip, ',' );
	  pair <string,string> pair7  ("zip",zip);   // value init
	  entries.push_back(pair7);

	  string other_services;
	  getline( myfile, other_services, '\n' );
	  pair <string,string> pair8  ("other_services",other_services);   // value init
	  entries.push_back(pair8);

	  Record add(entries); // Create record to add to table

	  geo->insert(add);  // Insert add record into geo
	  
	}
    
	myfile.close();
	return geo;

  }

}*/

int main()
{
	cout << "Enter any character to terminate program: \n";
  char c;
  cin >> c;
}

/*Table DB_Engine::natural_Join(Table table1, Table table2)
{
	vector<Attribute> common_attributes = get_Common_Attributes(table1, table2);

	vector<Tuple> new_tuples;

	for(Tuple tuple1 : table1.get_Tuples())
	{
		for(Tuple tuple2 : table2.get_Tuples())
		{
			if( tuple1.equal_On_Keys(tuple2, common_attributes) )
			{
				Tuple *new_tuple = new Tuple(tuple1);

				for(Attribute a : tuple2.get_Attributes())
				{
					bool unique = true;

					for(Attribute common_a : common_attributes)
					{
						if(a.is_Compatible(common_a) )
						{
							unique = false;
							break;
						}
					}

					if(unique)
						new_tuples.push_back(*new_tuple);
				}
			}
		}
	}

	Table *joined = new Table(table1.get_Name() + " joined with " + table2.get_Name(), new_tuples);

	return *joined;
}

vector<Attribute> get_Common_Attributes(Table table1, Table table2)
{
	vector<Attribute> common_attributes;

	for(Attribute a1 : table1.get_Tuples()[0])
	{
		for(Attribute a2 : table2.get_Tuples()[0])
		{
			if(a1.is_Compatible(a2))
				common_attributes.push_back(a1);
		}
	}

	return common_attributes;
}*/

