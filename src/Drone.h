#ifndef DRONE_H
#define DRONE_H

#include <string>

class Drone {
private:
    std::string id;
    int x;
    int y;
    int z;
    int prev_X;
    int prev_Y;
    int prev_Z;
    int battery;

public:
    static constexpr int MIN_VAL_COORD = -25000;
    static constexpr int MAX_VAL_COORD = 25000;

    explicit Drone(const std::string &id, int x = 0, int y = 0, int z = 0);

    const std::string &getId() const;
    int getXcoord() const;
    int getYcoord() const;
    int getZcoord() const;
    int getLastXcoord() const;
    int getLastYcoord() const;
    int getLastZcoord() const;
    int getBattery() const;

    bool move(int newX, int newY, int newZ);
    void comeToBase();
    void recharge();
    void showLocation() const;
    void showLastLocation() const;
    void showBattery() const;
};

#endif

