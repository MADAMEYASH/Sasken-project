// LaneManager.h                      // Header guard: filename for the header file
#ifndef LANEMANAGER_H                // Prevent multiple inclusion: start of header guard
#define LANEMANAGER_H                // Prevent multiple inclusion: define the guard

#include <iostream>                  // Include I/O stream library
using namespace std;                // Use the standard namespace

// Holds data for a single lane
struct LaneStatus {                 // Structure to store the status of one lane
    int vehicleCount = 0;          // Number of vehicles in the lane (default 0)
    bool hasAmbulance = false;     // Flag to indicate presence of ambulance
    bool hasVIP = false;           // Flag to indicate presence of VIP vehicle
    bool pedestrianWaiting = false;// Flag to indicate if pedestrian is waiting
};

// Manages all 4 lanes
class LaneManager {                // Class to manage traffic lanes
private:
    LaneStatus lanes[4];           // Array to store status for 4 lanes (N, E, S, W)

public:
    void addVehicle(int lane, int count);      // Adds given number of vehicles to a lane
    void markAmbulance(int lane);              // Marks ambulance presence in a lane
    void markVIP(int lane);                    // Marks VIP vehicle presence in a lane
    void addPedestrian(int lane);              // Sets pedestrian waiting flag for a lane
    void resetLane(int lane);                  // Resets lane status (after green light etc.)

    LaneStatus getLaneStatus(int lane);        // Returns current status of a specific lane
    void printLaneStatus();                    // Prints status of all lanes
};

#endif                                      // End of header guard
