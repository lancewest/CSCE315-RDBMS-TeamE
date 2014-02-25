#pragma once

#include "Parser.h"

class Bank_Application
{
private:
  DB_Engine db;
  int next_customer_id;
  int next_account_id;
  int next_transaction_id;
public:
  Bank_Application();

  void add_Customer(string name, string state_code);
  void add_Account(int customer_id);
  void add_Transaction(int account_from_id, int account_to_id, int amount);
  void delete_Transaction(int id);
  
  void view_Customer(int id);
  void view_Account(int id);
  void view_all_Customers();
  void view_all_Customers_Info_List();

  void change_Customer_State(int id, string new_state_code);

};