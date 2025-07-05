#include "TrafficLight.h"
#include <iostream>
#include <ctime>

TrafficLight::TrafficLight(int id) : state(RED), laneId(id) {}

void TrafficLight::setState(LightState newState) {
    std::lock_guard<std::mutex> lock(mtx);
    state = newState;
}

void TrafficLight::displayState() {
    std::string color;
    switch (state) {
        case RED: color = "\033[1;31mRED\033[0m"; break;
        case GREEN: color = "\033[1;32mGREEN\033[0m"; break;
        case YELLOW: color = "\033[1;33mYELLOW\033[0m"; break;
    }
    std::time_t now = std::time(nullptr);
    std::cout << "[" << std::ctime(&now) << "] Lane " << laneId << " Light: " << color;
    if (color.back() != '\n') std::cout << std::endl;
}
