#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <map>
#include <random>
#include <condition_variable>

using namespace std;

// ---------- ENUMS & CONSTANTS ----------
enum LightState { RED, GREEN, YELLOW };
const int MAX_LANES = 4;
const int GREEN_DURATION_BASE = 5; // seconds

// ---------- CLASS DEFINITIONS ----------

class Sensor {
public:
    int detectVehicles(); // Simulate number of vehicles on a lane
};

class TrafficLight {
private:
    LightState state;
    int laneId;
    mutex mtx;

public:
    TrafficLight(int id);

    void setState(LightState newState);
    LightState getState();
    void displayState();
};

class Lane {
public:
    int id;
    Sensor sensor;
    TrafficLight light;

    Lane(int id);
};

class TrafficController {
private:
    vector<Lane> lanes;
    mutex controllerMutex;
    condition_variable cv;

public:
    TrafficController(int numLanes);

    void monitorTraffic();     // Periodically check vehicle count
    void updateLights();       // Update light states based on vehicle density
    void runController();      // Main controller loop
};

// ---------- FUNCTION IMPLEMENTATIONS ----------

// ----- Sensor -----
int Sensor::detectVehicles() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 20); // simulate 0–20 vehicles
    return dis(gen);
}

// ----- TrafficLight -----
TrafficLight::TrafficLight(int id) : laneId(id), state(RED) {}

void TrafficLight::setState(LightState newState) {
    lock_guard<mutex> lock(mtx);
    state = newState;
}

LightState TrafficLight::getState() {
    lock_guard<mutex> lock(mtx);
    return state;
}

void TrafficLight::displayState() {
    lock_guard<mutex> lock(mtx);
    string color = (state == RED) ? "RED" : (state == GREEN) ? "GREEN" : "YELLOW";
    cout << "Lane " << laneId << " Light: " << color << endl;
}

// ----- Lane -----
Lane::Lane(int id) : id(id), light(id) {}

// ----- TrafficController -----
TrafficController::TrafficController(int numLanes) {
    for (int i = 0; i < numLanes; ++i) {
        lanes.emplace_back(i);
    }
}

void TrafficController::monitorTraffic() {
    // Collect vehicle data from all lanes
    for (auto& lane : lanes) {
        int vehicleCount = lane.sensor.detectVehicles();
        cout << "Lane " << lane.id << ": " << vehicleCount << " vehicles detected.\n";
        // Store vehicle count if needed
    }
}

void TrafficController::updateLights() {
    // Simple logic: Give green to lane with max vehicles
    int maxVehicles = -1, selectedLane = -1;

    for (auto& lane : lanes) {
        int vehicleCount = lane.sensor.detectVehicles(); // You may want to cache instead
        if (vehicleCount > maxVehicles) {
            maxVehicles = vehicleCount;
            selectedLane = lane.id;
        }
    }

    // Set all lights to RED
    for (auto& lane : lanes) {
        lane.light.setState(RED);
    }

    // Set selected lane to GREEN
    if (selectedLane != -1) {
        lanes[selectedLane].light.setState(GREEN);
        lanes[selectedLane].light.displayState();
        this_thread::sleep_for(chrono::seconds(GREEN_DURATION_BASE + maxVehicles / 4)); // dynamic duration
        lanes[selectedLane].light.setState(YELLOW);
        lanes[selectedLane].light.displayState();
        this_thread::sleep_for(chrono::seconds(2));
    }
}

void TrafficController::runController() {
    while (true) {
        monitorTraffic();
        updateLights();
        this_thread::sleep_for(chrono::seconds(1));
    }
}

// ---------- MAIN ----------
int main() {
    TrafficController controller(MAX_LANES);

    thread controllerThread(&TrafficController::runController, &controller);

    controllerThread.join();
    return 0;
}
