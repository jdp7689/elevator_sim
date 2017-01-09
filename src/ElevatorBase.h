/*
 * \file ElevatorBase.h
 * \date Nov 9, 2016
 * \author Josh Palmer
 */

#ifndef ELEVATORBASE_H_
#define ELEVATORBASE_H_

class ElevatorBase {
public:
    ElevatorBase();
    virtual void updateTime() = 0;
    virtual ~ElevatorBase();
};

#endif /* ELEVATORBASE_H_ */
