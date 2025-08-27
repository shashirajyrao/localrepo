#include "DroneManager.h"
#include <iostream>
#include <string>

int main() {
    DroneManager manager;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        manager.processCommand(line);
    }
    return 0;
}

