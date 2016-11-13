#ifndef PERSON_H
#define PERSON_H
#include <vector>
#include "sex.h"
#include <string>
using namespace std;
struct Person{
    string selfName;
    Person* partner;//look as left
    Person * child;//look as right
    sex itself;
    Person(string my_selfname, sex my_itself) :selfName(my_selfname), 
           itself(my_itself), partner(NULL), child(NULL){};
};

#endif