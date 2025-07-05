#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include <mutex>

enum LightState { RED, GREEN, YELLOW };

class TrafficLight {
private:
    LightState state;
    std::mutex mtx;
    int laneId;

public:
    TrafficLight(int id);
    void setState(LightState newState);
    void displayState();
};

#endif