#include "Bank_Application.h"


Bank_Application::Bank_Application()
{
  //Initialize db and id counters
  next_account_id = 1;
  next_customer_id = 1;
  next_transaction_id = 1;
  db = DB_Engine();

  //Create our 5 standard tables that application will use
  db.parse("CREATE TABLE customers (customer_id INTEGER, name VARCHAR(32), state VARCHAR(64)) PRIMARY KEY (customer_id);");

  db.parse("CREATE TABLE accounts (account_id INTEGER, balance INTEGER) PRIMARY KEY (account_id);");

  db.parse("CREATE TABLE transactions (transaction_id INTEGER, amount INTEGER) PRIMARY KEY (transaction_id);");

  db.parse("CREATE TABLE account_to_customer (account_id INTEGER, customer_id INTEGER) PRIMARY KEY (account_id);");

  db.parse("CREATE TABLE transaction_to_account (transaction_id INTEGER, account_from_id INTEGER, account_to_id INTEGER) PRIMARY KEY (transaction_id);");
}

void Bank_Application::add_Customer(string name, string state_code)
{
  db.parse("INSERT INTO customers VALUES FROM (" + to_string(next_customer_id) + ", \"" + name + "\", \"" + state_code + "\");");

  next_customer_id++;
}

void Bank_Application::add_Account(int customer_id)
{
  db.parse("INSERT INTO accounts VALUES FROM (" + to_string(next_account_id) + ", 0);");

  db.parse("INSERT INTO account_to_customer VALUES FROM (" + to_string(next_account_id) + ", " + to_string(customer_id) + ");");

  next_account_id++;
}

void Bank_Application::add_Transaction(int account_from_id, int account_to_id, int amount)
{
  //Gather necessary previous account balances
  vector<Condition> conditions_to_get_accounts = vector<Condition>();
  conditions_to_get_accounts.push_back( Condition("account_id", "==", to_string(account_from_id), "", true) );
  int from_account_amount = db.select( *(db.get_Table("accounts")), conditions_to_get_accounts).get_Tuples()[0].get_Attribute("balance")->get_Int_Value();

  conditions_to_get_accounts.empty();
  conditions_to_get_accounts.push_back( Condition("account_id", "==", to_string(account_to_id), "", true) );
  int to_account_amount = db.select( *(db.get_Table("accounts")), conditions_to_get_accounts).get_Tuples()[0].get_Attribute("balance")->get_Int_Value();


  //Execute transaction addition and balance updates on db
  db.parse("INSERT INTO transactions VALUES FROM (" + to_string(next_transaction_id) + ", " + to_string(amount) + ");");

  db.parse("INSERT INTO transaction_to_account VALUES FROM (" + to_string(next_transaction_id) + ", " + to_string(account_from_id) + ", " + to_string(account_to_id) + ");");

  db.parse("UPDATE accounts SET (amount = " + to_string(from_account_amount - amount) + ") WHERE (account_id == " + to_string(account_from_id) + ");" );

  db.parse("UPDATE accounts SET (amount = " + to_string(to_account_amount + amount) + ") WHERE (account_id == " + to_string(account_to_id) + ");" );

  next_transaction_id++;
}

void Bank_Application::delete_Transaction(int id)
{
  //Gather neccessary account ids, amounts, and balances
  vector<Condition> conditions = vector<Condition>();
  conditions.push_back( Condition("transaction_id", "==", to_string(id), "", true) );
  int amount = db.select( *(db.get_Table("transactions")), conditions).get_Tuples()[0].get_Attribute("amount")->get_Int_Value();

  int account_from_id = db.select( *(db.get_Table("transaction_to_account")), conditions).get_Tuples()[0].get_Attribute("account_from_id")->get_Int_Value();

  int account_to_id = db.select( *(db.get_Table("transaction_to_account")), conditions).get_Tuples()[0].get_Attribute("account_to_id")->get_Int_Value();

  conditions.empty();
  conditions.push_back( Condition("account_id", "==", to_string(account_from_id), "", true) );
  int account_from_balance = db.select( *(db.get_Table("accounts")), conditions).get_Tuples()[0].get_Attribute("balance")->get_Int_Value();

  conditions.empty();
  conditions.push_back( Condition("account_id", "==", to_string(account_to_id), "", true) );
  int account_to_balance = db.select( *(db.get_Table("accounts")), conditions).get_Tuples()[0].get_Attribute("balance")->get_Int_Value();


  //Execute transaction deletion and rollback on db
  db.parse("DELETE FROM transactions WHERE (transaction_id == " + to_string(id) + ");" );

  db.parse("DELETE FROM transaction_to_account WHERE (transaction_id == " + to_string(id) + ");" );

  db.parse("UPDATE accounts SET (amount = " + to_string(account_from_balance + amount) + ") WHERE (account_id == " + to_string(account_from_id) + ");" );

  db.parse("UPDATE accounts SET (amount = " + to_string(account_to_balance - amount) + ") WHERE (account_id == " + to_string(account_to_id) + ");" );
}

void Bank_Application::view_Customer(int id)
{
  db.parse( "SHOW select (customer_id == " + to_string(id) + ") customers;" );
  cout << "\n\nCustomers Accounts:\n";
  db.parse( "SHOW select (customer_id == " + to_string(id) + ") account_to_customer JOIN accounts" );
}

void Bank_Application::view_Account(int id)
{

}

void Bank_Application::view_all_Customers()
{

}

void Bank_Application::view_all_Customers_Info_List()
{

}


void Bank_Application::change_Customer_State(int id, string new_state_code)
{

}

