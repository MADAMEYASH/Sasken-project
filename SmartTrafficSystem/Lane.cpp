#include "Lane.h"

Lane::Lane(int i) : id(i), vehicleCount(0), hasVIP(false), hasPedestrian(false),
                    hasAmbulance(false), isGreen(false), waitTime(0), light() {}

void Lane::update(int count, bool vip, bool ped, bool amb) {
    std::lock_guard<std::mutex> lock(mtx);
    vehicleCount = count;
    hasVIP = vip;
    hasPedestrian = ped;
    hasAmbulance = amb;
}

void Lane::setGreen() {
    light.changeToGreen();
    printStatus();
}

void Lane::setRed() {
    light.changeToRed();
    printStatus();
}

void Lane::setYellow() {
    light.changeToYellow();
    printStatus();
}

void Lane::printStatus() {
    std::string color;
    switch (light.getState()) {
        case RED:    color = "RED"; break;
        case GREEN:  color = "GREEN"; break;
        case YELLOW: color = "YELLOW"; break;
    }

    std::cout << "Lane " << id << ": Vehicles=" << vehicleCount
              << (hasAmbulance ? " [AMBULANCE]" : "")
              << (hasVIP ? " [VIP]" : "")
              << (hasPedestrian ? " [PEDESTRIAN]" : "")
              << " | Light: " << color << std::endl;
}
