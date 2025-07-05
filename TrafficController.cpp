#include "TrafficController.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <ctime>

TrafficController::TrafficController(int numLanes) {
    for (int i = 0; i < numLanes; ++i) {
        lanes.emplace_back(std::make_unique<Lane>(i + 1));
    }
}

void TrafficController::monitorTraffic() {
    std::cout << "\n--- Monitoring Traffic ---" << std::endl;
    std::lock_guard<std::mutex> lock(controllerMutex);
    for (const auto& lane : lanes) {
        int count = lane->getSensor().detectVehicles();
        bool emergency = lane->getSensor().detectEmergency();
        lane->setVehicleCount(count);
        lane->setEmergency(emergency);

        std::cout << "Lane " << lane->getId() << ": " << count << " vehicles";
if (emergency)
    std::cout << " 🚑 [EMERGENCY]";
        std::cout << std::endl;
    }
}

void TrafficController::updateLights() {
    Lane* priorityLane = nullptr;
    {
        std::lock_guard<std::mutex> lock(controllerMutex);

        // Step 1: Emergency vehicle gets top priority
        for (auto& lane : lanes) {
            if (lane->isEmergencyDetected()) {
                priorityLane = lane.get();
                std::cout << ">>> 🚑 Emergency vehicle detected in Lane " << lane->getId() << "! Prioritizing...\n";
                break;
            }
        }

        // Step 2: If no emergency, select lane with most vehicles
        if (!priorityLane) {
            int maxVehicles = -1;
            for (auto& lane : lanes) {
                if (lane->getVehicleCount() > maxVehicles) {
                    maxVehicles = lane->getVehicleCount();
                    priorityLane = lane.get();
                }
            }
        }

        // Step 3: Set RED + WALK for all other lanes
        for (auto& lane : lanes) {
            if (lane.get() != priorityLane) {
                lane->getTrafficLight().setState(RED);
                lane->getTrafficLight().displayState();

                lane->getPedestrianSignal().setState(WALK);
                lane->getPedestrianSignal().displayState();
            }
        }
    }

    // Step 4: Selected priority lane - GREEN + DON'T WALK
    if (priorityLane) {
        priorityLane->getPedestrianSignal().setState(DONT_WALK);
        priorityLane->getPedestrianSignal().displayState();

        priorityLane->getTrafficLight().setState(GREEN);
        priorityLane->getTrafficLight().displayState();

        for (int t = 3; t > 0; --t) {
            std::cout << "GREEN light countdown: " << t << "s\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        priorityLane->getTrafficLight().setState(YELLOW);
        priorityLane->getTrafficLight().displayState();

        for (int t = 2; t > 0; --t) {
            std::cout << "YELLOW light countdown: " << t << "s\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
}


void TrafficController::runController() {
    while (true) {
        monitorTraffic();
        updateLights();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void TrafficController::addLane() {
    std::lock_guard<std::mutex> lock(controllerMutex);
    int newId = static_cast<int>(lanes.size()) + 1;
    lanes.emplace_back(std::make_unique<Lane>(newId));
    std::cout << "✅ New lane added: Lane " << newId << std::endl;
}