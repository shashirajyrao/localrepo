#include "Drone.h"
#include <iostream>
#include <cmath>

using std::cout;
using std::endl;
using std::string;

Drone::Drone(const string &id, int x, int y, int z)
    : id(id), x(x), y(y), z(z), prev_X(x), prev_Y(y), prev_Z(z), battery(100) {}

const string &Drone::getId() const { return id; }
int Drone::getXcoord() const { return x; }
int Drone::getYcoord() const { return y; }
int Drone::getZcoord() const { return z; }
int Drone::getLastXcoord() const { return prev_X; }
int Drone::getLastYcoord() const { return prev_Y; }
int Drone::getLastZcoord() const { return prev_Z; }
int Drone::getBattery() const { return battery; }

bool Drone::move(int newX, int newY, int newZ) {
    // clamp target into bounds first
    if (newX < MIN_VAL_COORD || newX > MAX_VAL_COORD ||
        newY < MIN_VAL_COORD || newY > MAX_VAL_COORD ||
        newZ < MIN_VAL_COORD || newZ > MAX_VAL_COORD) {
        return false;
    }

    double distanceFloat = std::sqrt(static_cast<double>((newX - x) * (newX - x) +
                                                         (newY - y) * (newY - y) +
                                                         (newZ - z) * (newZ - z)));
    int distance = static_cast<int>(distanceFloat + 0.5);
    if (battery < distance) {
        return false;
    }

    prev_X = x;
    prev_Y = y;
    prev_Z = z;

    x = newX;
    y = newY;
    z = newZ;
    battery -= distance;
    if (battery < 0) battery = 0;
    return true;
}

void Drone::comeToBase() {
    prev_X = x; prev_Y = y; prev_Z = z;
    x = 0; y = 0; z = 0;
    cout << "BASE REACHED" << endl;
}

void Drone::recharge() {
    battery = 100;
    cout << "RECHARGE DONE" << endl;
}

void Drone::showLocation() const {
    cout << "x=" << x << " y=" << y << " z=" << z << endl;
}

void Drone::showLastLocation() const {
    cout << "x=" << prev_X << " y=" << prev_Y << " z=" << prev_Z << endl;
}

void Drone::showBattery() const {
    cout << "BATTERY " << battery << "%" << endl;
}

