#include "Controller.h"
#include <thread>
#include <chrono>
#include <iostream>

Controller::Controller(std::vector<Lane>& l) : lanes(l) {}

void Controller::run(std::atomic<bool>& running) {
    while (running) {
        int selected = 0;
        for (int i = 1; i < lanes.size(); ++i) {
            if (lanes[i].hasAmbulance) { selected = i; break; }
            if (lanes[i].vehicleCount > lanes[selected].vehicleCount)
                selected = i;
        }
        for (int i = 0; i < lanes.size(); ++i) {
            lanes[i].isGreen = (i == selected);
        }
        std::cout << "Lane " << selected << " GREEN
";
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
}
