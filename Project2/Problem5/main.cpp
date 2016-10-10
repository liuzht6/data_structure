#include "Airport.h"
#include "init.h"
#include <random>
using namespace std;

int main() {
	int end_time, queue_limit, capacity, flight_num = 0;
	double arrival_rate, departure_rate, fuel_rate;

	initialize(end_time, capacity, queue_limit, arrival_rate, departure_rate, fuel_rate);

	default_random_engine generator;
	poisson_distribution<int> distribution_arrival(arrival_rate);
	poisson_distribution<int> distribution_departure(departure_rate);
	poisson_distribution<int> distribution_fuel(fuel_rate);

	Airport small_airport(capacity, queue_limit);

	for (int current_time = 0; current_time < end_time; current_time++) {
		int number_arrivals = distribution_arrival(generator);
		int number_fuel = distribution_fuel(generator);
		cout << number_arrivals << "   " << number_fuel << endl;
		for (int i = 0; i < number_arrivals; i++) {
			Plane current_plane(flight_num++, current_time, arriving, number_fuel);
			if (small_airport.can_land(current_plane) != true)
				small_airport.refuse(current_plane);
		}
		int number_departures = distribution_departure(generator);
		for (int j = 0; j < number_departures; j++) {
			Plane current_plane(flight_num++, current_time, departing);
			if (small_airport.can_depart(current_plane) != true)
				small_airport.refuse(current_plane);
		}
		small_airport.activity(current_time);
	}
	small_airport.shut_down(end_time);
	system("pause");
	return 0;
}
