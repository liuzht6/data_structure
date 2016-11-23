#include "FamilyAgenda.h"
#include "Person.h"
#include <string>
using namespace std;

void manageOneFamily(FamilyAgenda &agenda, string familyname) {
  cout << "1 - Marriage" << endl
       << "2 - Add Baby" << endl
       << "3 - Print" << endl
       << "0 - Quit" << endl;
  int functionNumber;
  while (cin >> functionNumber && functionNumber != 0) {
    switch (functionNumber) {
    case 1: {
      agenda.familyGetMarried(familyname);
      break;
    }
    case 2: {
      agenda.familyBornBaby(familyname);
      break;
    }
    case 3: {
      agenda.printFamily(familyname);
      break;
    }
    case 0: {
      cout << "HAHA" << endl;
      return;
    }
    default: {
      cout << "No matched number, please check your input" << endl;
      break;
    }
    }
    cout << endl << "Please enter what you want to do" << endl;
  }
}

int main() {
  FamilyAgenda Siri;
  cout << "Welcome to Family Agenda v0.0.1" << endl
       << "Please enter what you want to do" << endl
       << "1 - Creat a Family" << endl
       << "2 - Choose a Family to take actions" << endl
       << "3 - Remove a Family" << endl
       << "0 - Quit" << endl;
  int functionNumber;
  while (cin >> functionNumber && functionNumber != 0) {
    switch (functionNumber) {
    case 1: {
      Siri.creatFamily();
      break;
    }
    case 2: {
      string familyname;
      cout << "Please enter the family you want to manage" << endl;
      cin >> familyname;
      if (Siri.isFamilyExist(familyname))
        manageOneFamily(Siri, familyname);
      else
        cout << "Family doesn't exist" << endl;
      break;
    }
    case 3: {
      Siri.removeFamily();
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
    cout << endl << "Please enter what you want to do" << endl;
  }
}