#pragma once
#ifndef FAMILY_H_
#define FAMILY_H_
#include "Person.h"
#include <iostream>
#include <queue>
#include <string>
using namespace std;

class Family {
 public:
  Family(string name = "") : familyName(name) {
    if (familyName == "") {
      cout << endl << "Please enter family's name" << endl;
      cin >> this->familyName;
    }
    cout << endl << "Please enter founder's information" << endl;
    this->founder = new Person(male);
    this->members_total = 1;
  };

  ~Family() {
    clear(founder);
    members_total = 0;
  }

  // postOrder clear the family
  void clear(Person *root) {
    if (root != nullptr) {
      clear(root->partner);
      clear(root->child);
      delete root;
    }
  }

  // print the family
  void print(Person *root, int level) {
    if (root != NULL) {
      if (root != NULL) {
        for (int i = 0; i < level; i++) cout << "  ";
        if (level == 1)
          cout << "Partner: ";
        else if (level == 2)
          cout << "Children: ";
        cout << root->name << endl;

        print(root->partner, level + 1);
        print(root->child, level + 1);
      }
    }
  }

  // add partner
  void getPartner(string name) {
    Person *man = queryPersonByName(name);
    if (founder->name == name) {
      if (founder->partner != nullptr) {
        cout << name << "has had already married!" << endl;
      } else {
        cout << endl << "Please enter the wife's information" << endl;
        founder->partner = new Person(female);
        members_total++;
      }
    } else if (man != founder) {
      if (man->partner != nullptr) {
        cout << name << "has had already married!" << endl;
      } else {
        cout << endl << "Please enter the wife's information" << endl;
        man->partner = new Person(female);
        members_total++;
      }
    } else {
      cout << name << " doesn't exist!" << endl;
    }
  }

  // add child
  void bornBaby(string name) {
    Person *daddy = queryPersonByName(name);
    Person *mom = daddy->partner;
    if (founder->name == name) {
      Person *childChain = founder->partner;
      while (childChain->child != nullptr) {
        childChain = childChain->child;
      }
      cout << endl << "Please enter the baby's information" << endl;
      childChain->child = new Person();
      members_total++;
    } else if (daddy == founder) {
      cout << name << " doesn't exist!" << endl;
    } else if (daddy->partner == nullptr) {
      cout << name << " hasn't got married yet!" << endl;
    } else {
      Person *childChain = daddy->partner;
      while (childChain->child != nullptr) {
        childChain = childChain->child;
      }
      cout << endl << "Please enter the baby's information" << endl;
      childChain->child = new Person();
      members_total++;
    }
  }

  // remove daughter
  void remove_person(const string name) {
    auto &daughter = queryPersonByName(name);
    delete daughter;
    daughter = nullptr;
  }

  // find person by name
  Person *&queryPersonByName(const string name) {
    queue<Person *> familyQueue;
    familyQueue.push(founder);
    Person *p = nullptr;
    while (!familyQueue.empty()) {
      p = familyQueue.front();
      if (p->name == name) return p;
      familyQueue.pop();
      if (p->child != nullptr) familyQueue.push(p->child);
      if (p->partner != nullptr) familyQueue.push(p->partner);
    }
    return founder;
  }

  Person *getFounder() { return founder; }
  string getFamilyName() { return familyName; }
  int getSum_members() { return members_total; }

 private:
  Person *founder;
  int members_total;
  string familyName;
};

#endif  // !FAMILY_H_
