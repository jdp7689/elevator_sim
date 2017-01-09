/*
 * \file Elevator.h
 * \date Nov 3, 2016
 * \author Josh Palmer
 */

#ifndef ELEVATOR_H_
#define ELEVATOR_H_

#include "Person.h"
#include "Floor.h"
#include <vector>
#include <deque>

using namespace std;

/**
 * \class Elevator
 * \ingroup ElevatorSim
 *
 * \brief Logic for the movements and actions of an elevator
 *
 * \author Josh Palmer
 */


namespace elevator_motion {
typedef enum elevator_motion_e {
    STOP,
    STOPPING,
    MOVING_DOWN,
    MOVING_UP,
} elevator_motion_t;
}

class Elevator {
public:
    Elevator(unsigned int travel_time_between_floors);
    /// Destructor needed to fullfil rule of 3
    ~Elevator();
    Elevator(const Elevator &rhs);
    Elevator& operator=(const Elevator &rhs);

    /// Returns whether the elevator is full
    bool isFull();
    /// Returns whether the elevator is empty
    bool isEmpty();

    /// Update the time. Called when a second passes
    void updateTime(vector<Floor>& floors_waiting);

    /// Get average waiting time for people waiting for the elevator
    double getAvgTimeWaitingForElevator();
    /// Get average waiting time for people on the elevator
    double getAvgTimeWaitingOnElevator();

private:
    /// update the running totals
    void updateWaitingTimes(Person& person);

    /// All times in seconds
    const unsigned int time_to_stop = 2;
    /// The maximum number of passengers
    const unsigned int max_number_of_passengers = 8;
    /// Highest floor in the building
    const unsigned int highest_floor = 100;

    /// What floor we're currently on
    int current_floor;
    /// Transition period between floors
    int time_between_floors;
    /// How we're currently moving
    elevator_motion::elevator_motion_t current_motion;
    /// Total passengers serviced
    unsigned int total_passengers;
    /// Next floor to pickup a passenger
    int next_pickup_floor;
    /// Whether we're on our way to pick up a person
    bool picking_up_person;
    /// How much time total has been waited for this elevatir
    double total_time_waiting_for_elevator;
    /// How much time has been spent waiting on the elevator
    double total_time_waiting_on_elevator;
    /// Travel time between floors
    unsigned int travel_time_between_floors;
    /// The people currently on the elevator
    deque<Person> people_on;
};

#endif /* ELEVATOR_H_ */
