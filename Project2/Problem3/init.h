#include <iostream>
#include <iomanip>
using namespace std;

void initialize(int& end_time, int& capacity, int& queue_limit,
                double& arrival_rate, double& departure_rate) {
  cout << "This program simulates an airport with only one runway." << endl
       << "One plane can land or depart in each unit of time." << endl;
  cout << "Capacity of the airport? " << flush;
  cin >> capacity;
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