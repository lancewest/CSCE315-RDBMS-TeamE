#include "Simple_Parser.h"

int main()
{

  DB_Engine db;
  string current_line;

  for(;;) {
    getline(cin, current_line);

    if(current_line == "EXIT") {
      break;
    }

    Parser p(&db, current_line);
    p.parse();
  }

  return 0;

/*Read in from file
  cout << "\n\n\nSQL from file test\n========================\n";
  db.open("sql.txt");

  cout << "Enter any character to terminate program.\n";
  char c;
  cin >> c;
*/
}