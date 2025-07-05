#ifndef LANE_H
#define LANE_H

#include "Sensor.h"
#include "TrafficLight.h"
#include "PedestrianSignal.h"

class Lane {
private:
    int id;
    Sensor sensor;
    TrafficLight light;
    PedestrianSignal pedSignal;
    int vehicleCount;
    bool hasEmergency;

public:
    Lane(int laneId);
    int getId() const;
    int getVehicleCount() const;
    void setVehicleCount(int count);
    void setEmergency(bool flag);
    bool isEmergencyDetected() const;
    Sensor& getSensor();
    TrafficLight& getTrafficLight();
    PedestrianSignal& getPedestrianSignal();
};

#endif