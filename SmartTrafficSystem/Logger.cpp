#include "Logger.h"
#include <iomanip>

void Logger::logStatus(const std::vector<Lane>& lanes, int cycle) {
    std::ofstream file("traffic_log.txt", std::ios::app);

    std::time_t now = std::time(nullptr);
    file << "Cycle " << cycle << " - " << std::ctime(&now);

    for (const auto& lane : lanes) {
        std::string lightState;
        switch (lane.light.getState()) {
            case RED:    lightState = "RED"; break;
            case GREEN:  lightState = "GREEN"; break;
            case YELLOW: lightState = "YELLOW"; break;
        }

        file << "Lane " << lane.id
             << " | Vehicles: " << lane.vehicleCount
             << " | Light: " << lightState
             << " | Emergency: " << (lane.hasAmbulance ? "Yes" : "No")
             << "\n";
    }
    file << "--------------------------\n";
    file.close();
}
