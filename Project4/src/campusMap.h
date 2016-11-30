#ifndef CAMPUSMAP_H_
#define CAMPUSMAP_H_

#include <string>
#include <vector>
#include <memory>
#include <queue>
#include <map>
#include <set>
#include <iostream>
#include "sight.h"
using namespace std;

struct edgeVertex {
  string name;
  int length;
  shared_ptr<edgeVertex> next;
  edgeVertex(string n, int l, edgeVertex* nx = nullptr)
      : name(n), length(l), next(nx) {}
};

struct vertex {
  sight sightSpot;
  shared_ptr<edgeVertex> firstEdge;
  string name;
  vertex(sight s, edgeVertex* f = nullptr)
      : sightSpot(s), firstEdge(f), name(sightSpot.getSightName()) {}

  void addEdge(string name, int l) {
    auto edgePointer = this->firstEdge;
    if (edgePointer == nullptr) {
      this->firstEdge.reset(new edgeVertex(name, l));
    } else {
      while (edgePointer->next != nullptr) edgePointer = edgePointer->next;
      edgePointer->next.reset(new edgeVertex(name, l));
    }
  }
};

class campusMap {
 public:
  campusMap() {}

  campusMap(vector<vertex>& s, string name) : spots(s), campusName(name) {}

  vector<vertex>::iterator findSight(string name) {
    for (auto it = spots.begin(); it != spots.end(); it++) {
      if (it->name == name) return it;
    }
    return spots.end();
  }

  void addVertex(vertex& v) { spots.push_back(v); }

  // using Dijkstra algorithm
  void distanceDetect() {
    for (auto oneSpot : spots) {
      set<string> S, Q;  // S: detected, empty set
                         // Q: not detected, set of all verticles

      map<string, int> distance;
      for (auto e : spots) Q.insert(e.name);
      distance[oneSpot.name] = 0;

      while (Q.empty()) {
        auto minDistance = extractMin(Q, S);
        if (distance.find(minDistance.first) == distance.end() ||
            distance[minDistance.first] > minDistance.second) {
          Q.erase(minDistance.first);
          S.insert(minDistance.first);
        }
      }

      auto edge = oneSpot.firstEdge;
      while (edge != nullptr) {
        if (distance[this->findSight(edge->name)->name] >
            edge->length) {
          edge->length =
              distance[this->findSight(edge->name)->name];
        }
      }
    }
  }

  pair<string, int> extractMin(set<string> Q, set<string> S) {
    pair<string, int> minDistance;
    for (auto s : S) {
      for (auto e : Q) {
        auto edge = this->findSight(s)->firstEdge;
        while (edge != nullptr) {
          if (minDistance.second > edge->length &&
              edge->name == this->findSight(e)->name) {
            minDistance.first = edge->name;
            minDistance.second = edge->length;
          }
          edge = edge->next;
        }
      }
    }
    return minDistance;
  }

  vector<vertex> spots;

  string campusName;
};

#endif  // !CAMPUSMAP_H_