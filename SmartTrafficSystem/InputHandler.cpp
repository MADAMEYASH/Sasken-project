#include "InputHandler.h"
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

std::vector<Lane> InputHandler::getLaneInputs() {
    srand(time(0));
    std::vector<Lane> lanes;

    int numLanes = rand() % 9 + 2; // b/w 2 and 10
    for (int i = 0; i < numLanes; ++i) {
        Lane lane(i);
        int vehicles = rand() % 20 + 5;
        bool vip = (rand() % 10 == 0);         // ~10% chance
        bool ped = (rand() % 5 == 0);          // ~20% chance
        bool amb = (rand() % 15 == 0);         // ~7% chance
        lane.update(vehicles, vip, ped, amb);
        lanes.push_back(lane);
    }

    return lanes;
}

void InputHandler::run(std::vector<Lane>& lanes, std::atomic<bool>& running) {
    while (running) {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        for (auto& lane : lanes) {
            std::lock_guard<std::mutex> lock(lane.mtx);
            // Simulate new vehicles arriving
            lane.vehicleCount += rand() % 5;
            // Occasionally trigger new priorities
            if (rand() % 10 == 0) lane.hasVIP = true;
            if (rand() % 8 == 0)  lane.hasPedestrian = true;
            if (rand() % 20 == 0) lane.hasAmbulance = true;
        }
    }
}
