#include "Simulation.h"
#include "Random.h"
using namespace std;

int main() {
  int end_time;
  int queue_limit;
  int flight_num = 0;
  double arrival_rate, departure_rate;
  initialize(end_time, queue_limit, arrival_rate, departure_rate);
  Random varible;
  Runway small_airport(queue_limit);
  for (int current_time = 0; current_time < end_time; current_time++) {
    int number_arrivals = varible.poisson(arrival_rate);
    for (int i = 0; i < number_arrivals; i++) {
      Plane current_plane(flight_num++, current_time, arriving);
      if (small_airport.can_land(current_plane) != true) current_plane.refuse();
    }
    int number_departures = varible.poisson(departure_rate);
    for (int j = 0; j < number_departures; j++) {
      Plane current_plane(flight_num++, current_time, departing);
      if (small_airport.can_depart(current_plane) != true)
        current_plane.refuse();
    }
    Plane moving_plnae;
    switch (small_airport.activity(current_time, moving_plnae)) {
      case land:
        moving_plnae.land(current_time);
        break;
      case take_off:
        moving_plnae.fly(current_time);
        break;
      case idle:
        run_idle(current_time);
    }
  }
  small_airport.shut_down(end_time);
  return 0;
}