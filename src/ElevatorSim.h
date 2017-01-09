/*
 * \file ElevatorSim.h
 * \date Nov 4, 2016
 * \author Josh Palmer
 */

#ifndef ELEVATORSIM_H_
#define ELEVATORSIM_H_

#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include <sstream>
#include <fstream>
#include <array>
#include "Elevator.h"
#include "Floor.h"

using namespace std;

/**
 * \class ElevatorSim
 * \ingroup ElevatorSim
 *
 * \brief Class that runs the elevator simulation with a specified travel time between floors
 *
 * \author Josh Palmer
 */


class ElevatorSim {
public:
    ElevatorSim(string csv_filename, unsigned int travel_time_between_floors);
    /// Run the simulation
    void startSim();
    /// Returns the average waiting time for an elevator
    double getAvgTimeWaitingForElevator();
    /// Returns the average waiting time on an elevator
    double getAvgTimeWaitingOnElevator();

private:
    /// Number of elevators in the building
    const unsigned int num_elevators = 4;
    /// Reads the csv file and creates floor objects from the lines
    void readFile(string& csv_filename);
    /// Checks whether the simulation is finished or not
    bool isSimFinished();
    /// Calculates the stats
    void calculateStats();

    /// This will represent what's in the file
    /// floors wil be dequeued when they are "called" by a person (time in sim = time called on floor)
    deque<Floor> floors_in_timeline;
    /// Floors already in the simulation, but haven't been reached by an elevator
    vector<Floor> floors_waiting_for_elevator;
    /// Represents the elevators in the building
    vector<Elevator> elevators;
    /// The average waiting time for an elevator
    double avg_time_waiting_for_elevators;
    /// The average waiting time on an elevator
    double avg_time_waiting_on_elevators;
};

#endif /* ELEVATORSIM_H_ */
