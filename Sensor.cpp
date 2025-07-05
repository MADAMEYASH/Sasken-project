#include "Sensor.h"
#include <iostream>

Sensor::Sensor(int id) : laneId(id) {}

int Sensor::detectVehicles() {
    int count;
    std::cout << "[Input] Enter vehicle count for Lane " << laneId << ": ";
    std::cin >> count;
    return count;
}

bool Sensor::detectEmergency() {
    char input;
    std::cout << "[Input] Is there an emergency vehicle in Lane " << laneId << "? (y/n): ";
    std::cin >> input;
    return input == 'y' || input == 'Y';
}
