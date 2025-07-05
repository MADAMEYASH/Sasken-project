#include "PedestrianSignal.h"
#include <iostream>

PedestrianSignal::PedestrianSignal(int id) : state(WALK), laneId(id) {}

void PedestrianSignal::setState(PedSignalState newState) {
    std::lock_guard<std::mutex> lock(mtx);
    state = newState;
}

PedSignalState PedestrianSignal::getState() {
    return state;
}

void PedestrianSignal::displayState() {
    std::string status = (state == WALK) ? "WALK" : "DON'T WALK";
    std::cout << "Lane " << laneId << " Pedestrian Signal: " << status << std::endl;
}