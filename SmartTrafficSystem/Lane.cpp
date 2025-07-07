#include "Lane.h"

Lane::Lane(int i) : id(i), vehicleCount(0), hasVIP(false), hasPedestrian(false),
                    hasAmbulance(false), isGreen(false), waitTime(0) {}

void Lane::update(int count, bool vip, bool ped, bool amb) {
    std::lock_guard<std::mutex> lock(mtx);
    vehicleCount = count;
    hasVIP = vip;
    hasPedestrian = ped;
    hasAmbulance = amb;
}
