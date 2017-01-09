/*
 * \file Floor.cpp
 * \date Nov 4, 2016
 * \author Josh Palmer
 */

#include "Floor.h"
#include <iostream>

Floor::Floor(int floor_number, int start_time, Person person) :
        floor_number(floor_number), start_time(start_time), person(person), floor_called(
                false) {

}

Floor::Floor(const Floor& rhs) :
        floor_number(rhs.floor_number), start_time(rhs.start_time), person(
                rhs.person), floor_called(rhs.floor_called) {
}

Floor::~Floor() {

}

/// Get the time that a person presses the button on the floor
unsigned int Floor::getStartTime() {
    return start_time;
}

Floor& Floor::operator=(const Floor& rhs) {
    this->floor_number = rhs.floor_number;
    this->floor_called = rhs.floor_called;
    this->start_time = rhs.start_time;
    this->person = rhs.person;
    return *this;
}

/// Updates the time waiting of the person on the floor
void Floor::updateTime() {
    /// We're just waiting on the floor, so update the time waiting on the floor
    this->person.increaseTimeWaitingForElevator();
}

/// Marks the floor as called
void Floor::callFloor() {
    this->floor_called = true;
}

/// Returns whether the floor has been called
bool Floor::isCalled() {

    return this->floor_called;
}

/// Returns the person waiting on the floor
Person Floor::getPerson() {
    return this->person;
}

/// Returns the floor's number
unsigned int Floor::getFloorNumber() {
    return this->floor_number;
}
