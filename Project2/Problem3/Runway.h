/* Runway.h
 * Ecr23
 * 2016-Sep-29
 */

#ifndef RUNWAY_H_
#define RUNWAY_H_

#include <iostream>
#include <queue>
#include "Plane.h"
#include "enum.h"
using namespace std;

class Runway {
 public:
  //  constructors
  Runway(int n) : runway_num(n) {
    cout << "For runway " << runway_num
         << ", the propose is for? (1-both, 2-land, 3-depart) " << flush;
    int p;
    cin >> p;
    switch (p) {
      case 1:
        status = idle;
        change = 0;
        break;
      case 2:
        status = landing;
        change = 0;
        cout << "it can be used for aother way for some special times" << endl;
        break;
      case 3:
        status = takeoff;
        change = 0;
        cout << "it can be used for aother way for some special times" << endl;
        break;
    }

  }

  /* Post: Return the status of the Runway*/
  Runway_acticity state() { return status; }

  /* Post: A Plane takes off
   * Para: @time: time of the Plane need to take off
   *       @moving: the Plane taking off
   */
  void take_off(int time, const Plane& moving) { moving.fly(time); }

  /* Post: A Plane lands
   * Para: @time: time of the Plane need to land
   *       @moving: the Plane landing
   */
  void land(int time, const Plane& moving) { moving.land(time); }
  //change status
  void changeway() {
      if (change == 0 && status != landing) {
          status = landing;
          change = 1;
      }
      else if (change == 1) {
          status = takeoff;
          change = 0;
      }
  }
 private:
  int runway_num;
  Runway_acticity status;
  int change;
};

#endif  // !RUNWAY_H_
