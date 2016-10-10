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
        spe = false;
        break;
      case 2:
        status = landing;
        cout << "whether special? (1-yes, 2-no) ";
        int n;
        cin >> n;
        if (n == 1) {
            spe = true;
            cout << "it can be used for another way for some special times" << endl;
        } else {
            spe = false;
        }
        break;
      case 3:
        status = takeoff;
        spe = false;
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

  bool special() { return spe; }
 private:
  int runway_num;
  Runway_acticity status;
  bool spe;
};

#endif  // !RUNWAY_H_
