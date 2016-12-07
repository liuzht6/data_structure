#include "FamilyAgenda.h"
#include <string>
using namespace std;

int main() {
  FamilyAgenda Agenda;
  cout << "Welcome to Family Agenda v0.0, please enter what you want to do"
       << endl
       << "1 - Creat a Family" << endl
       << "2 - Choose a Family to take actions" << endl
       << "3 - Remove a Family" << endl
       << "4 - Show Family statics" << endl
       << "0 - Quit" << endl;
  int functionNumber;
  while (cin >> functionNumber && functionNumber != 0) {
    string Aname;
    string Fname;
    switch (functionNumber) {
      case 1: {
        cout << "Please enter the ancestor's name" << endl;
        cin >> Aname;
        cout << "Please enter the family's name" << endl;
        cin >> Fname;
        Person ancestor(Aname, male);
        if (Agenda.creatFamily(&ancestor, Fname))
          cout << "Creat success!" << endl;
        else
          cout << "Creat Failed! Duplicated Family name" << endl;
        break;
      }
      case 2: {
        cout << "Please enter the family's name" << endl;
        cin >> Fname;
        if (Agenda.queryFamilyByName(Fname) != nullptr)
          cout << "Query success!" << endl;
        else
          cout << "Query failed! Family doesn't exist'" << endl;
        break;
        
      }
      case 3: {
        cout << "Please enter the family's name" << endl;
        cin >> Fname;
        if (Agenda.removeFamily(Fname))
          cout << "Remove success!" << endl;
        else
          cout << "Remove failed! Family doesn't exist'" << endl;
        break;
      }
      case 4: {
        cout << Agenda.getFamilySum() << endl;
        break;
      }
      case 0: {
        cout << "Thanks for using. Goodbye" << endl;
        break;
      }
      default: {
        cout << "No matched number, please check your input" << endl;
        break;
      }
    }
  }
}