#ifndef SIGHT_H_
#define SIGHT_H_

#include <string>
using namespace std;

class sight {
 public:
  sight(string s, string i) : sightName(s), intro(i) {}

  string getSightName() { return this->sightName; }

  string getIntro() { return this->intro; }

 private:
  string sightName;
  string intro;
};

#endif  // !SIGHT_H_