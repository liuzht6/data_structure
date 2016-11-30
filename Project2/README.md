# Project2 - Simulation of an Airport
This program simulates an airport with several runways.  
One plane can land or depart in each unit of time.  
Folder `book` is program given on the textbook, and `mySimu` is my version.  

```
Project2/
├── book/
│   ├── Random.h
│   ├── main.cpp
│   └── Simulation.h
└── mySimu/
    ├── Airport.h
    ├── enum.h
    ├── init.h
    ├── Plane.h
    ├── Runway.h
    └── main.cpp

```

## Breif Introduction
In `main.cpp`, we use a for loop to simulate time and in every time unit, `Airport::activity()` will run once.   
### Input 
- Capacity of the airport. Land request will be refuesed if airport is full
- Time of the program. How many units of time will this program run
- Queue limit. Waiting queue's limit for both landing and depart requests. Requests will be refused if the queue is full
- Expected number of arrivals&departures per unit time. Random variable will genrate somme planes to take-off&land in every unit of time accordding to the expected number input
- Runways' information. Number of runways and its proporse ( both, land, takeoff)

### Output
- Activities in every time unit. If the runway is idle, then show "Runway is idle"
- A statical data table, including a lot of data

## To-do List
1. Output format in function `Airport::shut_down()` (刘钟涛)
2. Add comments (大家一起来)
3. Problem 1~6 on textbook. (刘俊良，刘钟涛) 
4. Makefile and a clearer file structure (刘俊良) 
5. Experiment report (彭高)
6. Test (gtest?) (再议)
