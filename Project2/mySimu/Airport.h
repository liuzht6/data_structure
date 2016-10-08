/* Airport.h
 * Ecr23
 * 2016-Sep-29
 */

#ifndef AIRPORT_H_
#define AIRPORT_H_

#include "Runway.h"
#include <vector>
#include <queue>
using namespace std;

bool operator<(const Plane& a, const Plane& b) { return a.prior() < b.prior(); }

class Airport {
 public:
  // constructors
  Airport() = default;
  Airport(int ca, int limit) : capacity(ca), queue_limit(limit) {
    size = 0;
    num_land_requests = num_takeoff_requests = 0;
    num_landings = num_takeoffs = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait = idle_time = 0;
    num_land_refused = num_takeoff_refused = 0;
    cout << "How many runways do you want? " << flush;
    int runway_num;
    cin >> runway_num;
    for (int i = 0; i < runway_num; i++) {
      Runway temp(i + 1);
      Runways.push_back(temp);
    }
  }

  /* Post: If possible, the Plane current is added to the landing queue and
   *       return true;
   *       Otherwise eturn false
   * para: current Plane need to land
   */
  bool can_land(const Plane& current) {
    num_land_requests++;
    if (size < capacity && landing_queue.size() < queue_limit) {
      landing_queue.push(current);
      size++;
      num_land_accepted++;
      return true;
    } else {
      num_land_refused++;
      return false;
    }
  }

  /* Post: the Plane current is added to the take-off queue and return true
   * para: current Plane need to take off
   */
  bool can_depart(const Plane& current) {
    num_takeoff_requests++;
    if (takeoff_queue.size() < queue_limit) {
      num_takeoff_accepted++;
      takeoff_queue.push(current);
      size--;
      return true;
    } else {
      num_takeoff_refused++;
      return false;
    }
  }

  void activity(int time, Plane& moving) {
    for (auto r : Runways) {
      if (!landing_queue.empty() &&
          (r.state() == landing || r.state() == idle)) {
        moving = landing_queue.front();
        r.land(time, landing_queue.front());
        landing_queue.pop();
        size++;
        num_landings++;
        land_wait += time - moving.clock_time();
      } else if (!takeoff_queue.empty() &&
                 (r.state() == takeoff || r.state() == idle)) {
        moving = takeoff_queue.front();
        r.take_off(time, takeoff_queue.front());
        takeoff_queue.pop();
        size--;
        num_takeoffs++;
        takeoff_wait += time - moving.clock_time();
      } else {
        idle_time++;
        cout << left << setw(8) << time
             << "No Planes need to land or take off now" << endl;
        return;
      }
    }
  }

  void refuse(Plane& current) {
    cout << "\tPlane " << current.id();
    if (current.state() == arriving) {
      cout << "directd to another airport" << endl;
      num_land_refused++;
    } else {
      cout << " told to try to takeoff again later" << endl;
      num_takeoff_refused++;
    }
  }

  void shut_down(int time) {
    cout << left;
    cout << "----------------------------------------------------------------"
            "--"
            "---"
         << endl;
    cout << setprecision(4) << fixed;
    cout << setw(60) << "Planes asking to land: " << num_land_requests << endl
         << setw(60) << "Planes asking to take off: " << num_takeoff_requests
         << endl
         << setw(60) << "Planes refused for landing: " << num_land_refused
         << endl
         << setw(60)
         << "Planes refused for takeing off: " << num_takeoff_refused << endl
         << setw(60) << "Planes accepted for landing: " << num_land_accepted
         << endl
         << setw(60)
         << "Planes accepted for taking off: " << num_takeoff_accepted << endl
         << setw(60) << "Planes that landed: " << num_landings << endl
         << setw(60) << "Planes that took off: " << num_takeoffs << endl
         << setw(60)
         << "Planes left in the landing queue: " << landing_queue.size() << endl
         << setw(60)
         << "Planes left in the takeoff queue: " << takeoff_queue.size() << endl
         << setw(60) << "Percentage of time runway idle: "
         << 100.0 * ((float)idle_time / (float)time) << "%" << endl
         << setw(60) << "Average wait in land queue: "
         << (float)land_wait / (float)num_landings << endl
         << setw(60) << "Average wait in take off queue: "
         << (float)takeoff_wait / (float)num_takeoffs << endl
         << setw(60) << "Average observed rate of planes wanting to land: "
         << (float)num_land_requests / (float)time << endl
         << setw(60) << "Average observed rate of planes wanting to take off: "
         << (float)num_takeoff_requests / (float)time << endl;

    cout << "----------------------------------------------------------------"
            "--"
            "---"
         << endl;
  }

 private:
  int size;                    // number of Planes in the airport
  int capacity;                // number of Planes the airport could accommodate
  int queue_limit;             // limit of both queues
  vector<Runway> Runways;      // Runways of an airoprt
  queue<Plane> landing_queue;  // Planes that waiting to land
  queue<Plane> takeoff_queue;  // Planes that waiting to take off

  // statics
  int idle_time;
  int takeoff_wait;
  int land_wait;
  int num_land_requests, num_takeoff_requests;
  int num_landings, num_takeoffs;
  int num_land_accepted, num_takeoff_accepted;
  int num_land_refused, num_takeoff_refused;
};

#endif  // !AIRPORT_H_