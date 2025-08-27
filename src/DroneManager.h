#ifndef DRONEMANAGER_H
#define DRONEMANAGER_H

#include "Drone.h"
#include <string>

class DroneManager {
private:
    Drone* drones[10];
    int count;

    Drone* findDrone(const std::string& id);

public:
    DroneManager();
    ~DroneManager();

    void processCommand(const std::string& command);
};

#endif

