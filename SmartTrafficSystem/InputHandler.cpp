#include "InputHandler.h"
#include <iostream>

std::vector<Lane> InputHandler::getLaneInputs() {
    int n;
    std::cout << "Enter number of lanes: ";
    std::cin >> n;
    std::vector<Lane> lanes;
    for (int i = 0; i < n; ++i) {
        lanes.emplace_back(i);
    }
    return lanes;
}

void InputHandler::run(std::vector<Lane>& lanes, std::atomic<bool>& running) {
    while (running) {
        int id, count;
        char vip, ped, amb;
        std::cout << "Lane ID: "; std::cin >> id;
        std::cout << "Vehicles: "; std::cin >> count;
        std::cout << "VIP? (y/n): "; std::cin >> vip;
        std::cout << "Pedestrian? (y/n): "; std::cin >> ped;
        std::cout << "Ambulance? (y/n): "; std::cin >> amb;
        if (id >= 0 && id < lanes.size())
            lanes[id].update(count, vip=='y'||vip=='Y', ped=='y'||ped=='Y', amb=='y'||amb=='Y');
    }
}
