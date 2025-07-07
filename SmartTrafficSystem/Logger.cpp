#include "Logger.h"
#include <fstream>

void Logger::logStatus(const std::vector<Lane>& lanes) {
    std::ofstream file("traffic_log.txt", std::ios::app);
    for (const auto& lane : lanes) {
        file << "Lane " << lane.id << ": " << lane.vehicleCount << " vehicles\n";
    }
    file << "\n";
}
