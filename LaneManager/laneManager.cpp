#include "LaneManager.h"                       // Include the corresponding header file

// Adds vehicles to a specific lane
void LaneManager::addVehicle(int lane, int count) {
    lanes[lane].vehicleCount += count;        // Increase vehicle count by 'count'
}

// Marks the presence of an ambulance in the lane
void LaneManager::markAmbulance(int lane) {
    lanes[lane].hasAmbulance = true;          // Set ambulance flag to true
}

// Marks the presence of a VIP in the lane
void LaneManager::markVIP(int lane) {
    lanes[lane].hasVIP = true;                // Set VIP flag to true
}

// Marks that a pedestrian is waiting in the lane
void LaneManager::addPedestrian(int lane) {
    lanes[lane].pedestrianWaiting = true;     // Set pedestrian flag to true
}

// Resets the lane status to default values
void LaneManager::resetLane(int lane) {
    lanes[lane] = LaneStatus();               // Create a new default LaneStatus object
}

// Returns the current status of the specified lane
LaneStatus LaneManager::getLaneStatus(int lane) {
    return lanes[lane];                       // Return copy of LaneStatus for the lane
}

// Prints the status of all 4 lanes
void LaneManager::printLaneStatus() {
    cout << "\n[Lane Status Report]" << endl; // Title of report
    for (int i = 0; i < 4; ++i) {             // Loop through all 4 lanes
        cout << "Lane " << i << ": "          // Print lane number
             << lanes[i].vehicleCount << " vehicles "   // Vehicle count
             << (lanes[i].hasAmbulance ? "[🚑] " : "")   // Ambulance emoji if present
             << (lanes[i].hasVIP ? "[VIP] " : "")        // VIP tag if present
             << (lanes[i].pedestrianWaiting ? "[🚶] " : "") // Pedestrian emoji if present
             << endl;                         // End line
    }
}

