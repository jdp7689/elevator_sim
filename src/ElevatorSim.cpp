/*
 * \file ElevatorSim.cpp
 * \date Nov 4, 2016
 * \author Josh Palmer
 */

#include "ElevatorSim.h"

ElevatorSim::ElevatorSim(string csv_filename, unsigned int travel_time_between_floors) :
        avg_time_waiting_for_elevators(0), avg_time_waiting_on_elevators(0) {
    unsigned int i;
    readFile(csv_filename);
    for (i = 0; i < this->num_elevators; i++) {
        elevators.push_back(Elevator(travel_time_between_floors));
    }
}

/// Reads the csv file and creates floor objects from the lines
void ElevatorSim::readFile(string& csv_filename) {
    ifstream infile(csv_filename);
    string line = "";
    /// Disregard the first line
    getline(infile, line);
    while (getline(infile, line)) {
        stringstream strstr(line);
        string start_time;
        string start_floor;
        string end_floor;

        getline(strstr, start_time, ',');
        getline(strstr, start_floor, ',');
        getline(strstr, end_floor, ',');

        this->floors_in_timeline.push_back(
                Floor(stoi(start_floor), stoi(start_time, nullptr, 10),
                        Person(stoi(end_floor, nullptr, 10))));
    }
}

/// Run the simulation
void ElevatorSim::startSim() {
    /// The seconds counter
    unsigned int time = 0;
    unsigned int i;
    while (!isSimFinished()) {
        /// Have we hit the point in the timeline that someone has pressed the button?
        while (time == this->floors_in_timeline.front().getStartTime()) {
            this->floors_waiting_for_elevator.push_back(
                    this->floors_in_timeline.front());
            this->floors_in_timeline.pop_front();
        }
        /// Update the elevators
        for (i = 0; i < this->elevators.size(); i++) {
            this->elevators[i].updateTime(this->floors_waiting_for_elevator);
        }

        /// Update the times of the people who are not on an elevator yet
        for (i = 0; i < this->floors_waiting_for_elevator.size(); i++) {
            this->floors_waiting_for_elevator[i].updateTime();
        }
        time++;
    }
    return calculateStats();
}

/// Calculates the stats
void ElevatorSim::calculateStats() {

    unsigned int i;
    for (i = 0; i < this->elevators.size(); i++) {
        this->avg_time_waiting_for_elevators =
                static_cast<double>(this->elevators[i].getAvgTimeWaitingForElevator());
        this->avg_time_waiting_on_elevators +=
                this->elevators[i].getAvgTimeWaitingOnElevator();
    }

    /// Compute average and return
    this->avg_time_waiting_for_elevators = this->avg_time_waiting_for_elevators
            / this->elevators.size();
    this->avg_time_waiting_on_elevators = this->avg_time_waiting_on_elevators
            / this->elevators.size();

}

/// Returns the average waiting time for an elevator
double ElevatorSim::getAvgTimeWaitingForElevator() {
    return this->avg_time_waiting_for_elevators;
}

/// Returns the average waiting time on an elevator
double ElevatorSim::getAvgTimeWaitingOnElevator() {
    return this->avg_time_waiting_on_elevators;
}

/// Checks whether the simulation is finished or not
bool ElevatorSim::isSimFinished() {
    /// The simulator is finished when there is no more floors in the timeline
    /// and there is no more floors in the queue
    /// and all elevators no longer have any passengers
    unsigned int i = 0;
    bool elevators_empty = true;
    for (i = 0; i < this->elevators.size(); i++) {
        if (!this->elevators[i].isEmpty()) {
            elevators_empty = false;
        }
    }

    return elevators_empty && this->floors_in_timeline.empty()
            && this->floors_waiting_for_elevator.empty();
}
