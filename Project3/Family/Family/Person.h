#pragma once
#ifndef PERSON_H
#define PERSON_H
#include "sex.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
struct Person {
  personSex sex;
  string name;

  // left
  Person *partner;

  // right
  Person *child;

  Person(personSex s = undefined, string n = "") : sex(s), name(n), partner(nullptr), child(nullptr) {
    if (n.empty()) {
      cout << "Please enter person's name" << endl;
      cin >> name;
    }
    
    if (s == undefined) {
      cout << "Please choose person's sex, 1 for male and 2 for female" << endl;
      int temp;
      while (cin >> temp) {
        if (temp == 1) {
          sex = male;
          break;
        }
        else if (temp == 2) {
          sex = female;
          break;
        }
        else {
          cout << "Invalid input" << endl;
        }
      }
    }
  };
};

#endif