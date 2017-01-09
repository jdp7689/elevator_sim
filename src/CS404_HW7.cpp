//============================================================================
// Name        : CS404_HW7.cpp
// Author      : Josh Palmer
// Description : Elevator Simulator
//============================================================================

#include <iostream>
#include "ElevatorSim.h"

// include log4cxx header files.
#include "log4cxx/logger.h"
#include "log4cxx/basicconfigurator.h"

using namespace std;

int main() {
    unsigned int travel_time_10_secs = 10;
    unsigned int travel_time_5_secs = 5;
    log4cxx::LoggerPtr logger(log4cxx::Logger::getLogger("ElevatorSimulator"));

    /// Run initial simulation with 10 seconds of travel time
    ElevatorSim sim("Mod10_Assignment_Elevators.csv", travel_time_10_secs);
    sim.startSim();

    /// Log using log4cxx
    log4cxx::BasicConfigurator::configure();
    LOG4CXX_INFO(logger,
            "Average time waiting for elevator with travel time = 10 secs: " << sim.getAvgTimeWaitingForElevator());

    LOG4CXX_INFO(logger,
            "Average time waiting on elevator with travel time = 10 secs: " << sim.getAvgTimeWaitingOnElevator());

    /// Start simulation with 5 seconds of travel time
    ElevatorSim sim2("Mod10_Assignment_Elevators.csv", travel_time_5_secs);
    sim2.startSim();

    LOG4CXX_INFO(logger,
            "Average time waiting for elevator with travel time = 5 secs: " << sim2.getAvgTimeWaitingForElevator());

    LOG4CXX_INFO(logger,
            "Average time waiting on elevator with travel time = 5 secs: " << sim2.getAvgTimeWaitingOnElevator());

    /// Calculate speedup
    LOG4CXX_INFO(logger,
            "Average percentage of speedup waiting for elevator: " <<
            ((sim.getAvgTimeWaitingForElevator() - sim2.getAvgTimeWaitingForElevator()) /
                    sim.getAvgTimeWaitingForElevator()) * 100 << "%");

    LOG4CXX_INFO(logger,
            "Average percentage of speedup waiting on elevator: " <<
            ((sim.getAvgTimeWaitingOnElevator() - sim2.getAvgTimeWaitingOnElevator()) /
                    sim.getAvgTimeWaitingOnElevator()) * 100 << "%");

    return 0;
}
