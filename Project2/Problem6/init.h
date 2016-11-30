#include <iostream>
#include <iomanip>
using namespace std;

void initialize(int& end_time, int& capacity, int& queue_limit) {
	cout << "This program simulates an airport with only one runway." << endl
		<< "One plane can land or depart in each unit of time." << endl;
	cout << "Capacity of the airport? " << flush;
	cin >> capacity;
	cout << "Up to what number of planes can be waiting to land "
		<< "or take off at any time? " << flush;
	cin >> queue_limit;
	cout << "How many units of time will the simulation run? " << flush;
	cin >> end_time;
}