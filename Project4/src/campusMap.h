#ifndef CAMPUSMAP_H_
#define CAMPUSMAP_H_

#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <string>
#include <stack>
#include <vector>
#include "sight.h"
using namespace std;

#define INFINITY_LENGTH 99999

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
  vertex(sight s, edgeVertex* f = nullptr) : sightSpot(s), firstEdge(f) {
    name = s.getSightName();
  }

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

  void findShortestPath(string from, string to) {
    set<string> Q;
    map<string, int> dist;
    map<string, string> prev;
    for (auto e : spots) {
      dist[e.name] = INFINITY_LENGTH;
      prev[e.name] = "";
      Q.insert(e.name);
    }

    dist[from] = -1;

    while (!Q.empty()) {
      auto u = extractMin(Q, dist);
      
      if (u == "") {
        if (dist[to] == INFINITY_LENGTH) {
          cout << "Found failed" << endl;
          return;
        } else {
          break;
        }
      }

      Q.erase(u);
      

      auto edge = this->findSight(u)->firstEdge;
      while (edge != nullptr) {
        auto alt = dist[u] + edge->length;
        if (dist[edge->name] == 0 || alt < dist[edge->name]) {
          dist[edge->name] = alt;
          prev[edge->name] = u;
        }
        edge = edge->next;
      }
    }

    stack<string> path;
    auto previousNode = prev[to];
    while (previousNode != from) {
      path.push(previousNode);
      previousNode = prev[previousNode];
    }

    cout << "the Path is: ";
    cout << from;
    while (!path.empty()) {
      cout << "->" << path.top();
      path.pop();
    }
    cout << "->" << to << endl;
    cout << "the legnth is: " << dist[to] << endl;
  }

  string extractMin(set<string>& Q, const map<string, int>& dist) {
    pair<string, int> minVertex;
    minVertex.second = INFINITY_LENGTH;
    for (auto e : dist) {
      if (Q.find(e.first) != Q.end() && e.second != 0 &&
          e.second < minVertex.second) {
        minVertex = e;
      }
    }
    return minVertex.first;
  }

  int findDistance(string f, string t) {
    auto fromIt = this->findSight(f);
    auto edge = fromIt->firstEdge;
    while (edge != nullptr) {
      if (edge->name == t)
        return edge->length;
      else
        edge = edge->next;
    }
    return INFINITY_LENGTH;
  }

  vector<vertex> spots;
  string campusName;
};

#endif  // !CAMPUSMAP_H_
