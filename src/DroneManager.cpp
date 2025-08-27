#include "DroneManager.h"
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;

DroneManager::DroneManager() : count(0) {
    for (int i = 0; i < 10; i++) drones[i] = nullptr;
}

DroneManager::~DroneManager() {
    for (int i = 0; i < count; i++) {
        delete drones[i];
    }
}

Drone* DroneManager::findDrone(const string& id) {
    for (int i = 0; i < count; i++) {
        if (drones[i] && drones[i]->getId() == id) return drones[i];
    }
    return nullptr;
}

void DroneManager::processCommand(const string& command) {
    std::stringstream ss(command);
    string cmd; ss >> cmd;

    if (cmd == "CREATE_DRONE") {
        string id; int x = 0, y = 0, z = 0;
        ss >> id;
        if (!(ss >> x >> y >> z)) { x = y = z = 0; }

        if (findDrone(id)) {
            cout << "CREATE_DRONE FAILED. DRONE " << id << " ALREADY EXISTS" << endl;
            return;
        }
        if (count >= 10) {
            cout << "CREATE_DRONE FAILED. LIMIT REACHED" << endl;
            return;
        }
        drones[count++] = new Drone(id, x, y, z);
        cout << "CREATE_DRONE " << id << " DONE" << endl;
    }
    else if (cmd == "MOVE") {
        string id; int x, y, z;
        ss >> id >> x >> y >> z;
        Drone* d = findDrone(id);
        if (!d) return;

        bool moved = d->move(x, y, z);
        if (!moved) {
            cout << "false" << endl;
            return;
        }

        cout << "true" << endl;
    }
    else if (cmd == "COME_TO_BASE") {
        string id; ss >> id;
        Drone* d = findDrone(id);
        if (d) d->comeToBase();
    }
    else if (cmd == "SHOW_LOC") {
        string id; ss >> id;
        Drone* d = findDrone(id);
        if (d) d->showLocation();
    }
    else if (cmd == "SHOW_LAST_LOC") {
        string id; ss >> id;
        Drone* d = findDrone(id);
        if (d) d->showLastLocation();
    }
    else if (cmd == "SHOW_BATTERY") {
        string id; ss >> id;
        Drone* d = findDrone(id);
        if (d) d->showBattery();
    }
    else if (cmd == "RECHARGE") {
        string id; ss >> id;
        Drone* d = findDrone(id);
        if (d) d->recharge();
    }
    else if (cmd == "DELETE_DRONE") {
        string id; ss >> id;
        for (int i = 0; i < count; i++) {
            if (drones[i] && drones[i]->getId() == id) {
                delete drones[i];
                for (int j = i; j < count - 1; j++) {
                    drones[j] = drones[j + 1];
                }
                drones[count - 1] = nullptr;
                count--;
                cout << "DELETE_DRONE " << id << " DONE" << endl;
                if (count == 0) {
                    cout << "STOPPING DRONE SERVER... BYE!" << endl;
                    std::exit(0);
                }
                return;
            }
        }
        cout << "DELETE_DRONE FAILED. DRONE " << id << " DOES NOT EXIST" << endl;
    }
}

