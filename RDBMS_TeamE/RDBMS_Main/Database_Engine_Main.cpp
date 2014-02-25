#include "Bank_Application.h"

/*int main()
{
  Bank_Application app = Bank_Application();
  string input; //for string input

  cout << "Welcome to our Banking Application!\n\n";

  while(input != "QUIT") {
    app.add_Customer()
  }
}*/



/*     Below is the code for the old main method which gives direct access to 
       database commands and was primarily used to test the parser          */

int main()
{

  DB_Engine db;
  string current_line;

  cout << "Enter a database command or query::\n";
  cout << "Eg. OPEN filename\n";

  for(;;) {
    getline(cin, current_line);

    if(current_line == "EXIT") {
      break;
    }

    Parser p(&db, current_line);
    p.parse();
  }

  return 0;

  //Read in from file
  //cout << "\n\n\nSQL from file test\n========================\n";
  //db.open("sql.txt");

  //cout << "Enter any character to terminate program.\n";
  //char c;
  //cin >> c;

}
