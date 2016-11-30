#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

enum Runway_activity { idle, land, take_off };
enum Plane_status { null, arriving, departing };

void initialize(int& end_time, int& queue_limit, double& arrival_rate,
                double& departure_rate) {
  cout << "This program simulates an airport with only one runway." << endl
       << "One plane can land or depart in each unit of time." << endl;
  cout << "Up to what number of planes can be waiting to land "
       << "or take off at any time? " << flush;
  cin >> queue_limit;
  cout << "How many units of time will the simulation run? " << flush;
  cin >> end_time;
  bool acceptable;
  do {
    cout << "Expected number of arrivals per unit time? " << flush;
    cin >> arrival_rate;
    cout << "Expected number of departures per unit time? " << flush;
    cin >> departure_rate;
    if (arrival_rate < 0.0 || departure_rate < 0.0)
      cerr << "These ratess must be nonnegative" << endl;
    else
      acceptable = true;
    if (acceptable && arrival_rate + departure_rate > 1.0)
      cerr << "Safety Warning!" << endl;
  } while (!acceptable);
}

void run_idle(int time) {
  cout << left << setw(8) << time << "Runway is idle" << endl;
}

class Plane {
 public:
  // constructors
  Plane() = default;
  Plane(int flt, int time, Plane_status state = null, int p = 1)
      : flt_num(flt), clock(time), status(state) {
    cout << "\t";
    cout << "Plane " << flt_num << " ready to "
         << ((status == arriving) ? "land." : "take off.") << endl;
  }

  // Post: Processes a Plane wanting to use Runway, when the Queue is full
  void refuse() const {
    cout << "\t";
    cout << "Plane " << flt_num;
    if (status == arriving)
      cout << "directd to another airport" << endl;
    else
      cout << " told to try to takeoff again later" << endl;
  }

  // Post: Processes a Plane tha id
  void land(int time) const {
    int wait = time - clock;
    cout << left << setw(8) << time << "Plane " << flt_num << " landed after "
         << wait << " time unit" << ((wait > 1) ? "s" : "")
         << " in the land queue" << endl;
  }

  // Post: Processes a Plane that is taking off at the specific time
  void fly(int time) const {
    int wait = time - clock;
    cout << left << setw(8) << time << "Plane " << flt_num << " took off after "
         << wait << " time unit" << ((wait > 1) ? "s" : "")
         << " in the takeoff queue" << endl;
  }

  // Post: Return the time that the Plane entered the airport system
  int clock_time() const { return clock; }

 private:
  int flt_num;          // flight number of the plane
  int clock;            // arrival time at system
  Plane_status status;  // plane's status
};

class Runway {
 public:
  /* Post: The RUnway data members are initialized to record no prior Runway
    use and to record the limit on queue sizes*/
  Runway(int limit) {
    queue_limit = limit;
    num_land_requests = num_takeoff_requesets = 0;
    num_landings = num_takeoffs = 0;
    num_land_accepted = num_takeoff_accepted = 0;
    land_wait = takeoff_wait = idle_time = 0;
    num_land_refused = num_takeoff_refused = 0;
  }

  /* Post: If possible, Plane current is added to the landing queue */
  bool can_land(const Plane& current) {
    num_land_requests++;
    if (landing.size() < queue_limit) {
      landing.push(current);
      num_land_accepted++;
      return true;
    } else {
      num_land_refused++;
      return false;
    }
  }

  /* Post: If possible, Plane current is added to the takeoff queue */
  bool can_depart(const Plane& current) {
    num_takeoff_requesets++;
    if (takeoff.size() < queue_limit) {
      takeoff.push(current);
      num_takeoff_accepted++;
      return true;
    } else {
      num_takeoff_refused++;
      return false;
    }
  }

  Runway_activity activity(int time, Plane& moving) {
    Runway_activity in_progress;
    if (!landing.empty()) {
      moving = landing.front();
      landing.pop();
      in_progress = land;
      land_wait += time - moving.clock_time();
      num_landings++;
    } else if (!takeoff.empty()) {
      moving = takeoff.front();
      takeoff.pop();
      in_progress = take_off;
      takeoff_wait += time - moving.clock_time();
      num_takeoffs++;
    } else {
      in_progress = idle;
      idle_time++;
    }
    return in_progress;
  }

  void shut_down(int time) {
    cout << left;
    cout << "------------------------------------------------------------------"
            "---"
         << endl;
    cout << setprecision(4) << fixed;
    cout << setw(60) << "Planes asking to land: " << num_land_requests << endl
         << setw(60) << "Planes asking to take off: " << num_takeoff_requesets
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
         << setw(60) << "Planes left in the landing queue: " << landing.size()
         << endl
         << setw(60) << "Planes left in the takeoff queue: " << takeoff.size()
         << endl
         << setw(60) << "Percentage of time runway idle: "
         << 100.0 * ((float)idle_time / (float)time) << "%" << endl
         << setw(60) << "Average wait in land queue: "
         << (float)land_wait / (float)num_landings << endl
         << setw(60) << "Average wait in take off queue: "
         << (float)takeoff_wait / (float)num_takeoffs << endl
         << setw(60) << "Average observed rate of planes wanting to land: "
         << (float)num_land_requests / (float)time << endl
         << setw(60) << "Average observed rate of planes wanting to take off: "
         << (float)num_takeoff_requesets / (float)time << endl;

    cout << "------------------------------------------------------------------"
            "---"
         << endl;
  }

 private:
  queue<Plane> landing;
  queue<Plane> takeoff;
  int queue_limit;

  // total number
  int idle_time;
  int takeoff_wait;
  int land_wait;
  int num_land_requests, num_takeoff_requesets;
  int num_landings, num_takeoffs;
  int num_land_accepted, num_takeoff_accepted;
  int num_land_refused, num_takeoff_refused;
};