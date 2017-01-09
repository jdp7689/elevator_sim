/*
 * \file Person.cpp
 * \date Nov 3, 2016
 * \author Josh Palmer
 */

#include "Person.h"
#include <stdlib.h>
using namespace std;

Person::Person(int end_floor) :
        end_floor(end_floor), time_waiting_for_elevator(0), time_waiting_on_elevator(
                0) {

}

Person::~Person() {

}

Person::Person(const Person &rhs) :
        end_floor(rhs.end_floor), time_waiting_for_elevator(
                rhs.time_waiting_for_elevator), time_waiting_on_elevator(
                rhs.time_waiting_on_elevator) {

}

/// Returns the floor the passenger is trying to get to
unsigned int Person::getEndFloor() {
    return this->end_floor;
}

/// Increments the time waited for the elevator
void Person::increaseTimeWaitingForElevator() {
    this->time_waiting_for_elevator++;
}

/// Increments the time waited on the elevator
void Person::increaseTimeOnElevator() {
    this->time_waiting_on_elevator++;
}

Person& Person::operator=(const Person& rhs) {

    this->end_floor = rhs.end_floor;
    this->time_waiting_for_elevator = rhs.time_waiting_for_elevator;
    this->time_waiting_on_elevator = rhs.time_waiting_on_elevator;
    return *this;
}

/// Returns the time waited for the elevator
unsigned int Person::getTimeWaitingForElevator() {
    return this->time_waiting_for_elevator;
}
/// Return the time waited on the elevator
unsigned int Person::getTimeWaitingOnElevator() {
    return this->time_waiting_on_elevator;
}
