/*
 * \file Person.h
 * \date Nov 3, 2016
 * \author Josh Palmer
 */

#ifndef PERSON_H_
#define PERSON_H_

/**
 * \class Person
 * \ingroup ElevatorSim
 *
 * \brief A person waiting for and traveling on an elevator
 *
 * \author Josh Palmer
 */

class Person {
public:
    Person(int end_floor);
    Person(const Person &rhs);
    Person& operator=(const Person& rhs);
    ~Person();

    /// Returns the time waited for the elevator
    unsigned int getTimeWaitingForElevator();
    /// Return the time waited on the elevator
    unsigned int getTimeWaitingOnElevator();
    /// Returns the floor the passenger is trying to get to
    unsigned int getEndFloor();
    /// Increments the time waited for the elevator
    void increaseTimeWaitingForElevator();
    /// Increments the time waited on the elevator
    void increaseTimeOnElevator();


private:
    /// The destination floor
    unsigned int end_floor;
    /// Total time waited for the elevator
    unsigned int time_waiting_for_elevator;
    /// Total time waited on the elevator
    unsigned int time_waiting_on_elevator;
};

#endif /* PERSON_H_ */
