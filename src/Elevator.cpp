/*
 * \file Elevator.cpp
 * \date Nov 3, 2016
 * \author Josh Palmer
 */

#include "Elevator.h"
#include <iostream>
#include <exception>

Elevator::Elevator(unsigned int travel_time_between_floors) :
        current_floor(0), time_between_floors(0), current_motion(
                elevator_motion::STOP), total_passengers(0), next_pickup_floor(
                0), picking_up_person(false), total_time_waiting_for_elevator(
                0), total_time_waiting_on_elevator(0), travel_time_between_floors(travel_time_between_floors){

}

Elevator::~Elevator() {

}

Elevator::Elevator(const Elevator &rhs) :
        current_floor(rhs.current_floor), time_between_floors(
                rhs.time_between_floors), current_motion(rhs.current_motion), total_passengers(
                rhs.total_passengers), next_pickup_floor(rhs.next_pickup_floor), picking_up_person(
                rhs.picking_up_person), total_time_waiting_for_elevator(
                rhs.total_time_waiting_for_elevator), total_time_waiting_on_elevator(
                rhs.total_time_waiting_on_elevator), travel_time_between_floors(rhs.travel_time_between_floors){

}

Elevator& Elevator::operator=(const Elevator &rhs) {
    this->current_floor = rhs.current_floor;
    this->time_between_floors = rhs.time_between_floors;
    this->current_motion = rhs.current_motion;
    this->total_passengers = rhs.total_passengers;
    this->next_pickup_floor = rhs.next_pickup_floor;
    this->picking_up_person = rhs.picking_up_person;
    this->total_time_waiting_for_elevator = rhs.total_time_waiting_for_elevator;
    this->travel_time_between_floors = rhs.travel_time_between_floors;
    return *this;
}

/// Returns whether the elevator is full
bool Elevator::isFull() {
    return max_number_of_passengers == this->people_on.size();
}

/// Returns whether the elevator is empty
bool Elevator::isEmpty() {
    return 0 == this->people_on.size();
}

/// Update the time. Called when a second passes
void Elevator::updateTime(vector<Floor>& floors_waiting) {
    unsigned int i;
    /// Go through scenarios for when the elevator is stopped
    if (this->current_motion == elevator_motion::STOP) {
        /// First, see if there is anyone to drop off or pick up

        /// Anyone getting off?
        if (this->people_on.size()) {
            for (i = 0; i < this->people_on.size(); i++) {
                if (this->people_on[i].getEndFloor() == this->current_floor) {
                    updateWaitingTimes(this->people_on[i]);
                    this->people_on.erase(this->people_on.begin() + i);
                    i--;
                }
            }
        }

        /// Anyone getting on? Don't pick anyone up on the way if we're called
        /// doing this to simplify logic
        for (i = 0; i < floors_waiting.size(); i++) {
            /// Add the person to the elevator and remove from the queue if it isn't already called and our elevator isn't full
            if (floors_waiting[i].getFloorNumber() == this->current_floor
                    && !isFull()) {
                this->people_on.push_back(floors_waiting[i].getPerson());
                floors_waiting.erase(floors_waiting.begin() + i); // remove from the waiting list
                i--; // update index because we just deleted a floor. This is to make sure we don't miss anything
                this->total_passengers++;
                this->picking_up_person = false;
            }
        }

        /// Now figure out what to do next
        /// If there are passengers on board, then go to their destination
        if (this->people_on.size()) {
            this->next_pickup_floor = this->people_on.front().getEndFloor();

        } else {
            /// If no one is on the elevator, then go get someone
            for (i = 0; i < floors_waiting.size(); i++) {
                if (!floors_waiting[i].isCalled()) {
                    this->next_pickup_floor =
                            floors_waiting[i].getFloorNumber();
                    floors_waiting[i].callFloor();
                    this->picking_up_person = true;

                    break;
                }
            }
        }

        /// Now get the direction of where to go
        if ((this->next_pickup_floor - this->current_floor) > 0) {
            this->current_motion = elevator_motion::MOVING_UP;
        } else if ((this->next_pickup_floor - this->current_floor) < 0) {
            this->current_motion = elevator_motion::MOVING_DOWN;
        }
        /// Go through conditions of what to do when the elevator is moving
    } else if (this->current_motion == elevator_motion::MOVING_UP
            || this->current_motion == elevator_motion::MOVING_DOWN) {
        this->time_between_floors++;

        if (this->time_between_floors == this->travel_time_between_floors) {
            this->time_between_floors = 0;

            if (this->current_motion == elevator_motion::MOVING_UP) {
                this->current_floor++;
                if (this->current_floor > highest_floor) {
                    throw "Elevator went too high";
                }
            } else {
                /// Can't go to negative floors!
                if (this->current_floor == 0) {
                    throw "Elevator going to negative floors";
                }
                this->current_floor--;
            }

            /// Check to see if we're stopping for anyone on the elevator
            if (this->people_on.size()) {
                for (i = 0; i < this->people_on.size(); i++) {
                    if (this->people_on[i].getEndFloor()
                            == this->current_floor) {
                        this->current_motion = elevator_motion::STOPPING;
                        break;
                    }
                }
            } else if (this->next_pickup_floor == this->current_floor) { /// probably not needed
                this->current_motion = elevator_motion::STOPPING;
            }
            /// Check to see if we're stopping to pick someone up
            else {
                bool found_one = false;
                for (i = 0; i < floors_waiting.size() && !found_one; i++) {
                    /// Add the person to the elevator and remove from the queue if it isn't already called and our elevator isn't full
                    if (!floors_waiting[i].isCalled()
                            && floors_waiting[i].getFloorNumber()
                                    == this->current_floor && !isFull()) {
                        /// Only pick up the person if we're on the way or we're called to the floor
                        if (!this->picking_up_person
                                || this->next_pickup_floor
                                        == this->current_floor) {
                            floors_waiting[i].callFloor();
                            this->current_motion = elevator_motion::STOPPING;
                            found_one = true;
                        }
                    }
                }
            }
        }
    } else if (this->current_motion == elevator_motion::STOPPING) {
        this->time_between_floors++;
        if (this->time_between_floors == this->time_to_stop) {
            this->current_motion = elevator_motion::STOP;
            this->time_between_floors = 0;
        }
    }
    /// Update times of passengers
    for (i = 0; i < this->people_on.size(); i++) {
        this->people_on[i].increaseTimeOnElevator();
    }
}

/// update the running totals
void Elevator::updateWaitingTimes(Person& person) {
    this->total_time_waiting_for_elevator += person.getTimeWaitingForElevator();
    this->total_time_waiting_on_elevator += person.getTimeWaitingOnElevator();

}

/// Get average waiting time for people waiting for the elevator
double Elevator::getAvgTimeWaitingForElevator() {
    return this->total_time_waiting_for_elevator / this->total_passengers;
}
/// Get average waiting time for people on the elevator
double Elevator::getAvgTimeWaitingOnElevator() {
    return this->total_time_waiting_on_elevator / this->total_passengers;
}

