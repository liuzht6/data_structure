#ifndef FAMILYAGENDA_H
#define FAMILYAGENDA_H
#include "Family.h"
#include "Person.h"
#include <set>
#include <iostream>
using namespace std;
class FamilyAgenda {
 public:
  FamilyAgenda() { family_amount = 0; }

  ~FamilyAgenda() {
    for (auto current_family = all_family.begin();
         current_family != all_family.end(); current_family++) {
      (*current_family)->clear((*current_family)->getFounder());
      Family* tmp = *current_family;
      all_family.erase(*current_family);
      delete tmp;
    }
    family_amount = 0;
  }
  
  // query family by familyname
  Family* queryFamilyByName(const string& familyname) {
    for (auto current_family = all_family.begin();
         current_family != all_family.end(); current_family++) {
      if ((*current_family)->get_familyname() == familyname) {
        return (*current_family);
      }
    }
    return nullptr;
  }

  // create a family
  bool creatFamily(Person* ancestor, string familyname) {
    for (auto current_family = all_family.begin();
         current_family != all_family.end(); current_family++)
      if ((*current_family)->get_familyname() == familyname) return false;
    Family* new_family = new Family(ancestor, familyname);
    all_family.insert(new_family);
    family_amount++;
    return true;
  }

  // remove a family
  bool removeFamily(string familyname) {
    for (auto current_family = all_family.begin();
         current_family != all_family.end(); current_family++) {
      if ((*current_family)->get_familyname() == familyname) {
        (*current_family)->clear((*current_family)->getFounder());
        Family* tmp = *current_family;
        all_family.erase(*current_family);
        delete tmp;
        family_amount--;
        return true;
      }
    }
    return false;
  }

  // get the amount of families
  int getFamilySum() { return family_amount; }

 private:
  set<Family*> all_family;  // Families, the set of families
  int family_amount;
};

#endif