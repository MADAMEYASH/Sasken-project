#include "Lane.h"

Lane::Lane(int laneId)
    : id(laneId), sensor(laneId), light(laneId), pedSignal(laneId), vehicleCount(0), hasEmergency(false) {}

int Lane::getId() const { return id; }
int Lane::getVehicleCount() const { return vehicleCount; }
void Lane::setVehicleCount(int count) { vehicleCount = count; }
void Lane::setEmergency(bool flag) { hasEmergency = flag; }
bool Lane::isEmergencyDetected() const { return hasEmergency; }
Sensor& Lane::getSensor() { return sensor; }
TrafficLight& Lane::getTrafficLight() { return light; }
PedestrianSignal& Lane::getPedestrianSignal() { return pedSignal; }