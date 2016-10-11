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
public:  // constructors
	Plane() = default;
	Plane(int flt, int time, Plane_status state = null, int f = 0)
		: flt_num(flt), clock(time), status(state), fuel(f) {
		cout << left << setw(8) << time << "Plane " << flt_num << " ready to "
			<< ((status == arriving) ? "land." : "take off") << endl;
	}

	// Post: Processes a Plane that is landing at the specific time
	void land(int time) const {
		int wait = time - clock;
		cout << time << "\tPlane " << flt_num << " landed after " << wait << " time unit"
			<< ((wait == 1) ? "" : "s") << " in the land queue" << endl;
	}

	// Post: Processes a Plane that is taking off at the specific time
	void fly(int time) const {
		int wait = time - clock;
		cout << time << "\tPlane " << flt_num << " took off after " << wait << " time unit"
			<< ((wait == 1) ? "" : "s") << " in the takeoff queue" << endl;
	}

	// Post: Return the flight number of the plane
	int flight_num() const { return flt_num; }

	// Post: Return the time that the Plane entered the airport system
	int clock_time() const { return clock; }

	// Post: Return Plane's fuel
	int fuel_num() const { return fuel; }

	// Post: Return Plane's priority
	int prior() const { return priority; }

	// Post: Return Plane's id
	int id() const { return flt_num; }

	// Post: Return Plane's status
	Plane_status state() const { return status; }

	//overload operator
	Plane operator = (const Plane & other) {
		this->flt_num = other.flight_num();
		this->priority = other.prior();
		this->clock = other.clock_time();
		this->fuel = other.fuel_num();
		this->status = other.state();
		return *this;
	}

private:
	int flt_num;          // flight number of the plane
	int priority;         // priority of the plane
	int clock;            // arrival time at system
	int fuel;             // fuel of the plane
	Plane_status status;  // plane's status
};

#endif  // !PLANE_H_

