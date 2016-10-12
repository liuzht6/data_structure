/* Plane.h
 * Ecr23
 * 2016-Sep-29
 */

#ifndef PLANE_H_
#define PLANE_H_

#include <iostream>
#include <iomanip>
#include "enum.h"
using namespace std;

class Plane {
 public:
  // constructors
  Plane(){};
  Plane(int flt, int time, Plane_status state = null, int p = 1)
      : flt_num(flt), priority(p), clock(time), status(state) {
    cout << left << setw(8) << time << "Plane " << flt_num << " ready to "
         << ((status == arriving) ? "land." : "take off") << endl;
  }

  /* Post: Processes a Plane that is landing at the specific time */
  void land(int time) const {
    int wait = time - clock;
    cout << "\tPlane " << flt_num << " landed after " << wait << " time unit"
         << ((wait == 1) ? "" : "s") << " in the land queue" << endl;
  }

  /* Post: Processes a Plane that is taking off at the specific time */
  void fly(int time) const {
    int wait = time - clock;
    cout << "\tPlane " << flt_num << " took off after " << wait << " time unit"
         << ((wait == 1) ? "" : "s") << " in the takeoff queue" << endl;
  }

  /* Post: Return the time that the Plane entered the airport system */
  int clock_time() const { return clock; }

  /* Post: Return Plane's priority */
  int prior() const { return priority; }

  /* Post: Return Plane's id */
  int id() const { return flt_num; }

  /* Post: Return Plane's status */
  Plane_status state() const { return status; }

 private:
  int flt_num;          // flight number of the plane
  int priority;         // priority of the plane
  int clock;            // arrival time at system
  int fuel;             // fuel of the plane
  Plane_status status;  // plane's status
};

#endif  // !PLANE_H_
