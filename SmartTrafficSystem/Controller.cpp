#include "Controller.h"
#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>

using namespace std;

Controller::Controller(std::vector<Lane>& lanes) : lanes(lanes) {}

int Controller::selectPriorityLane() {
    for (const auto& lane : lanes) {
        if (lane.hasAmbulance) return lane.id;
    }
    for (const auto& lane : lanes) {
        if (lane.hasVIP) return lane.id;
    }
    for (const auto& lane : lanes) {
        if (lane.hasPedestrian) return lane.id;
    }
    int maxLane = 0;
    int maxVehicles = lanes[0].vehicleCount;
    for (const auto& lane : lanes) {
        if (lane.vehicleCount > maxVehicles) {
            maxVehicles = lane.vehicleCount;
            maxLane = lane.id;
        }
    }
    return maxLane;
}

void Controller::run(std::atomic<bool>& running) {
    while (running) {
        int priority = selectPriorityLane();

        for (auto& lane : lanes) {
            std::lock_guard<std::mutex> lock(lane.mtx);
            if (lane.id == priority) {
                lane.setGreen();
            } else {
                lane.setRed();
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(5)); // Green duration

        for (auto& lane : lanes) {
            std::lock_guard<std::mutex> lock(lane.mtx);
            if (lane.id == priority) {
                lane.setYellow();
            }
        }

        std::this_thread::sleep_for(std::chrono::seconds(2)); // Yellow duration

        // Optional: Write log file
        ofstream log("traffic_log.txt", ios::app);
        log << "[Cycle Log]\n";
        for (const auto& lane : lanes) {
            log << "Lane " << lane.id << ": Vehicles=" << lane.vehicleCount
                << ", Light=" << lane.light.getStateName()
                << (lane.hasAmbulance ? " [Ambulance]" : "")
                << (lane.hasVIP ? " [VIP]" : "")
                << (lane.hasPedestrian ? " [Pedestrian]" : "")
                << "\n";
        }
        log << "Priority Lane: " << priority << "\n\n";
        log.close();
    }
}
