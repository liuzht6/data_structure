#include "guide.h"

int main() {
  guide Siri;
  auto v = Siri.thisMap.spots;
  Siri.thisMap.findShortestPath("Library", "West-Stadium");
  for (int i = 0; i < v.size(); i++) {
    for (int j = 0; j < v.size(); j++) {
      if (i != j) {
        Siri.thisMap.findShortestPath(v[i].name, v[j].name);
      }
    }
  }
}