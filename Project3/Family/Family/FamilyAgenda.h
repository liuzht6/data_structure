#pragma once
#ifndef FAMILYAGENDA_H
#define FAMILYAGENDA_H
#include "Family.h"
#include "Person.h"
#include <iostream>
#include <map>
#include <string>
#include <memory>
using namespace std;
class FamilyAgenda {
public:
  FamilyAgenda() : familyNumber(0) {}

  void creatFamily() {
    cout << "Please enter the family's name" << endl;
    string familyname;
    cin >> familyname;
    Family* temp = new Family(familyname);
    if (familyMap.find(familyname) != familyMap.end())
      cout << "Family " << familyname << " already exist" << endl;
    else
      familyMap.insert(make_pair(temp->getFamilyName(), temp));
  }

  void removeFamily() {
    cout << "Please enter the family you want to remove" << endl;
    string familyname;
    cin >> familyname;
    auto it = queryFamilyByName(familyname);
    if (it != familyMap.end()) {
      familyMap.erase(it);
      cout << "Remove success" << endl;
    }
  }

  void familyBornBaby(string familyname) {
    auto it = queryFamilyByName(familyname);
    if (it != familyMap.end()) {
      cout << "Please enter a male's name in this family" << endl;
      string daddy;
      cin >> daddy;
      it->second->bornBaby(daddy);
    }
  }

  void familyGetMarried(string familyname) {
    auto it = queryFamilyByName(familyname);
    if (it != familyMap.end()) {
      cout << "Please enter a male's name in this family" << endl;
      string husband;
      cin >> husband;
      it->second->getPartner(husband);
    }
  }

  void printFamily(string familyname) {
    auto it = queryFamilyByName(familyname);
    if (it != familyMap.end()) {
      it->second->print(it->second->getFounder(), 0);
    }
  }

  map<string, Family *>::iterator queryFamilyByName(string familyname) {
    auto it = familyMap.find(familyname);
    if (it == familyMap.end())
      cout << "Query failed, family " << familyname << " doesn't exist" << endl;
    return it;
  }

  bool isFamilyExist(string familyname) {
    auto it = familyMap.find(familyname);
    if (it == familyMap.end())
      return false;
    else
      return true;
  }

  int getFamilySum() { return familyNumber; }

private:
  // Families, the set of families
  map<string, Family *> familyMap;
  int familyNumber;
};

#endif


/*
  void removeFamily() {
    auto it = queryFamilyByName();
    if (it != familyMap.end()) {
      familyMap.erase(it);
      cout << "Remove success" << endl;
    }
  }
  
  void creatFamily() {
    cout << "Please enter the family's name" << endl;
    string familyname;
    cin >> familyname;
    Family *temp = new Family(familyname);
    if (familyMap.find(familyname) != familyMap.end())
      cout << "Family " << familyname << " already exist" << endl;
    else
      familyMap.insert(make_pair(temp->getFamilyName(), temp));
  }

  void removeFamily() {
    auto it = queryFamilyByName();
    if (it != familyMap.end()) {
      familyMap.erase(it);
      cout << "Remove success" << endl;
    }
  }

  void removeFamily(string familyname) {
    auto it = queryFamilyByName();
    if (it != familyMap.end()) {
      familyMap.erase(it);
      cout << "Remove success" << endl;
    }
  }

  void familyBornBaby() {
    auto it = queryFamilyByName();
    if (it != familyMap.end()) {
      cout << "Please enter a male's name in this family" << endl;
      string daddy;
      cin >> daddy;
      it->second->bornBaby(daddy);
    }
  }

  void familyGetMarried() {
    auto it = queryFamilyByName();
    if (it != familyMap.end()) {
      cout << "Please enter a male's name in this family" << endl;
      string husband;
      cin >> husband;
      it->second->getPartner(husband);
    }
  }

  void printFamily() {
    auto it = queryFamilyByName();
    if (it != familyMap.end()) {
      it->second->print(it->second->getFounder(), 0);
    }
  }

  map<string, Family *>::iterator queryFamilyByName() {
    cout << "Please enter the family's name" << endl;
    string familyname;
    cin >> familyname;
    return queryFamilyByName(familyname);
  }

*/