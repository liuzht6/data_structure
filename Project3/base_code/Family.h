#ifndef FAMILY_H
#define FAMILY_H
#include <string>
#include <vector>
#include <iostream>
#include "sex.h"
#include "Person.h"
using namespace std;
class Family {
 public:
  Family(Person* ancestor, string name)
      : founder(ancestor), familyName(name), members_total(1){};

  ~Family() {
    clear(founder);
    members_total = 0;
  }
  
  // clear the family
  void clear(Person* root) {
    if (root != NULL) {
      clear(root->partner);
      clear(root->child);
      delete root;
    }
  }

  // print the family
  void print(Person* root, int level) {
    if (root != NULL) {
      if (root != NULL) {
        for (int i = 0; i < level; i++) cout << "  ";
        cout << root->selfName << endl;
        print(root->partner, level + 1);
        print(root->child, level + 1);
      }
    }
  }

  // add partner
  bool marry_other(Person* wife, string name) {
    Person* man = NULL;
    man = find_person(founder, name);
    if (man != NULL) {
      man->partner = wife;
      members_total++;
      return true;
    } else {
      return false;
    }
  }

  // add child
  void born_baby(Person* baby, string name) {
    Person* man = NULL;
    man = find_person(founder, name);
    if (man != NULL && man->partner != NULL) {
      Person* newchild = man->partner;
      while (newchild->child != NULL) {
        newchild = newchild->child;
      }
      newchild->child = baby;
      members_total++;
    }
  }

  // remove daughter
  void remove_person(string name) {
    Person* front = find_front(founder, name);
    Person* re_person = front->child;
    front->child = front->child->child;
    delete re_person;
  }

  Person* find_front(Person* found, string name) {
    if (found != nullptr) {
      cout << found->selfName << " " << name << endl;
      if (found->child != nullptr)
        if (found->child->selfName == name) return found;
      find_front(found->partner, name);
      find_front(found->child, name);
    }
  }

  // find person by name
  Person* find_person(Person* found, string name) {
    if (found != nullptr) {
      if (found->selfName == name) return found;
      find_person(found->partner, name);
      find_person(found->child, name);
    } else {
      return nullptr;
    }
  }

  // get founder
  Person* getFounder() { return founder; }
  // get familyname
  string get_familyname() { return familyName; }
  // get sum of members
  int getSum_members() { return members_total; }

 private:
  Person* founder;
  string familyName;
  int members_total;
};

#endif