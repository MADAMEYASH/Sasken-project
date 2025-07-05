#ifndef TRAFFIC_CONTROLLER_H
#define TRAFFIC_CONTROLLER_H

#include <vector>
#include <mutex>
#include <condition_variable>
#include "Lane.h"

class TrafficController {
private:
    std::vector<std::unique_ptr<Lane>> lanes;
    std::mutex controllerMutex;
    std::condition_variable cv;

public:
    TrafficController(int numLanes);
    void monitorTraffic();
    void updateLights();
    void runController();
    void addLane();
};
#endif