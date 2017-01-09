/*
 * \file Floor.h
 * \date Nov 4, 2016
 * \author Josh Palmer
 */

#ifndef FLOOR_H_
#define FLOOR_H_

#include "Person.h"

using namespace std;

/**
 * \class Floor
 * \ingroup ElevatorSim
 *
 * \brief Represents a single floor in the simulation
 *
 * \author Josh Palmer
 */

class Floor{
public:
    Floor(int floor_number, int start_time, Person person);
    Floor(const Floor& rhs);
    Floor& operator= (const Floor& rhs);
    ~Floor();

    /// Updates the time waiting of the person on the floor
    void updateTime();
    /// Returns the person waiting on the floor
    Person getPerson();
    /// Returns the floor's number
    unsigned int getFloorNumber();
    /// Marks the floor as called
    void callFloor();
    /// Returns whether the floor has been called
    bool isCalled();
    /// Get the time that a person presses the button on the floor
    unsigned int getStartTime();

private:
    /// The floor's number
    unsigned int floor_number;
    /// Time person presses the elevator button
    unsigned int start_time;
    /// The person waiting on the floor
    Person person;
    /// Going to use this as a semaphore of sorts to prevents 2 elevators from getting the same person
    bool floor_called;

};

#endif /* FLOOR_H_ */
