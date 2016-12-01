#ifndef GUIDE_H_
#define GUIDE_H_

#include <fstream>
#include "json/json.h"
#include "campusMap.h"
#include <exception>
#include <initializer_list>

using namespace std;
using namespace Json;

void readFromFile(vector<campusMap>& v) {
  fstream fs;
  fs.open("../storage/database.json");

  vector<string> campusList = {"east", "north", "south", "zhuhai", "shenzhen"};

  Reader reader;
  Value root;

  if (!reader.parse(fs, root, false)) return;

  for (auto e : campusList) {
    Value spots = root[e];
    vector<vertex> sights;
    if (!spots.empty()) {
      for (int i = 0; i < spots.size(); ++i) {
        Value oneSpot = spots[i];
        string strName = oneSpot["name"].asString();
        string strIntro = oneSpot["intro"].asString();
        vertex tmpSight(sight(strName, strIntro), nullptr);

        Json::Value distance = oneSpot["distance"];
        for (int j = 0; j < spots.size(); j++) {
          string tempName = spots[j]["name"].asString();
          if (tempName != strName && distance[tempName].asInt() != 0)
            tmpSight.addEdge(tempName, distance[tempName].asInt());
        }
        sights.push_back(tmpSight);
      }
      v.push_back(campusMap(sights, e + "Campus"));
    }
  }
  fs.close();
}

class guide {
 public:
  guide() {
    readFromFile(SYSUguide);
    start();
  }

  //~guide() { syncToFile(SYSUguide); }

  void start() {
    cout << "Welcome to SYSU, Please choose which campus to sightsee" << endl;
    cout << "1 : East Campus | 0 : exit" << endl;
    int num;
    cin >> num;
    switch (num) {
      case 1: {
        try {
          this->thisMap = this->findCampus("eastCampus");
        } catch (const string& errorMessage) {
          cerr << errorMessage << endl;
          exit(0);
        }
        break;
      }
      case 0: {
        cout << "Thank You, Goodbye" << endl;
        return;
      }
      default:
        cout << "Please try again" << endl;
        break;
    }
    cout << "Please enter what you want to do" << endl;
    cout << "1 : Show sight | 0 : exit" << endl;
    int functionNum;
    int flag = 1;
    while (flag == 1 && cin >> functionNum) {
      switch (functionNum) {
        case 1: {
          cout << "Please enter the sight's name" << endl;
          string sightName;
          cin >> sightName;
          this->showSight(sightName);
          break;
        }
        case 0: {
          flag = 0;
          break;
        }
        default:
          break;
      }
    }
  }

  void showSight(string name) {
    auto it = thisMap.findSight(name);
    if (it != thisMap.spots.end()) {
      cout << "Sopt's name: " << it->sightSpot.getSightName() << endl;
      cout << "Spot's name: " << it->sightSpot.getIntro() << endl;
      cout << "Spot's distance: " << endl;
      auto edge = it->firstEdge;
      while (edge != nullptr) {
        cout << "\tTo " << edge->name << ": " << edge->length << endl;
        edge = edge->next;
      }
    } else {
      cout << "Spot sight " << name << " doesn't exist" << endl;
    }
  }

  void addSight() {
    string name;
    string intro;
    cout << "Please enter sight's name" << endl;
    cin >> name;
    cout << "Please enter sight's introduction" << endl;
    cin >> intro;
    vertex temp(sight(name, intro));
    cout << "Please enter any other sights' name connected to this sight. End "
            "with 0."
         << endl;
    string distanceName;
    while (cin >> distanceName && distanceName != "0") {
      int length;
      cout << "Please enter the distance between " << distanceName << " to "
           << name << endl;
      cin >> length;
      temp.addEdge(distanceName, length);
    }
    thisMap.addVertex(temp);
  }

 private:
  campusMap& findCampus(const string name) {
    for (auto& e : SYSUguide) {
      if (e.campusName == name) return e;
    }
    throw string("Campus doesn't exist!");
  }

  vector<campusMap> SYSUguide;
  public: campusMap thisMap;
};

#endif