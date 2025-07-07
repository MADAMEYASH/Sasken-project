#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

struct Lane {
    int id;
    int vehicleCount;
    bool hasVIP;
    bool isGreen;
    int waitTime;
    bool hasFiretruck;
    bool hasAmbulance;

    Lane(int id) : id(id), vehicleCount(0), hasVIP(false), hasFiretruck(false)
                   ,hasAmbulance(false), isGreen(false), waitTime(0) {}
};

vector<string> weather = {
        "Sunny", "Cloudy", "Windy", "Rainy", "Stormy", "Snowy", "Foggy"
    };
string today_weather(){
    random_device rd;           
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0,weather.size() - 1);
    return weather[dist(gen)];
}
string weat = today_weather();
void displayStatus(const vector<Lane>& lanes, int priorityLane, const string& reason) {
    cout << "\nOUTPUT:\n";
    int intensity = 0;
    for(int i = 0;i < weather.size();i++){
        if(weat == weather[i]){
            intensity = i + 1;
        }
    }
    cout << "Today`s weather : " << weat << endl; 
    cout << "+--------+------------+---------------+-----------+---------------------+----------+\n";
    cout << "| Lane   | Vehicles   | Light         | Intensity | Priority Reason     | WaitTime |\n";
    cout << "+--------+------------+---------------+-----------+---------------------+----------+\n";

    for (const auto& lane : lanes) {
        cout << "| Lane " << lane.id << " |     "
             << lane.vehicleCount << "     |  "
             << (lane.isGreen ? "   GREEN     " : "RED   [WALK] ")<< " |  " << intensity <<"        |";

        if (lane.id == priorityLane) {
            cout << reason;
        } else {
            if (lane.hasAmbulance)       cout << "     Ambulance     ";
            else if (lane.hasVIP)        cout << "        VIP        ";
            else if (lane.hasFiretruck)  cout << "     Firetruck     ";
            else                         cout << "                   ";
        }

        cout << "|    " << lane.waitTime << "s   |\n";
    }

    cout << "+--------+------------+---------------+-----------+--------------------+----------+\n";
    cout << "\nNext priority: Lane " << priorityLane << " (" << reason << ")\n" << endl;
}

int selectPriorityLane(vector<Lane>& lanes, string &reason) {
    for (const auto& lane : lanes) {
        if (lane.hasAmbulance) {
            reason = "     Ambulance     ";
            return lane.id;
        }
    }
    
    for (const auto& lane : lanes) {
        if (lane.hasFiretruck) {
            reason = "     Firetruck     ";
            return lane.id;
        }
    }
    for (const auto& lane : lanes) {
        if (lane.hasVIP) {
            reason = "        VIP        ";
            return lane.id;
        }
    }

    int maxLane = 0;
    int maxCount = lanes[0].vehicleCount;
    for (const auto& lane : lanes) {
        if (lane.vehicleCount > maxCount) {
            maxCount = lane.vehicleCount;
            maxLane = lane.id;
        }
    }

    reason = "   Most vehicles    ";
    return maxLane;
}

int main() {

    int numLanes;
    cout << "Enter number of traffic lanes: ";
    cin >> numLanes;

    vector<Lane> lanes;
    for (int i = 0; i < numLanes; ++i) {
        Lane lane(i);
        char vip, ped, amb;
        cout << "Is there a [ VIP ] at Lane " << i << "? (y/n): ";
        cin >> vip;
        lane.hasVIP = (vip == 'y' || vip == 'Y');
        
        if(!lane.hasVIP){
        cout << "Enter vehicle count for Lane " << i << ": ";
        cin >> lane.vehicleCount;
        }
        
        cout << "Ambulance Sirens" << i << "? (y/n): ";
        cin >> amb;
        lane.hasAmbulance = (amb == 'y' || amb == 'Y');
        
        cout << "Is there an [ Firetruck ] waiting at Lane " << i << "? (y/n): ";
        cin >> amb;
        lane.hasFiretruck = (amb == 'y' || amb == 'Y');

        lanes.push_back(lane);
    }

    // Run simulation for 5 green light cycles
    for (int round = 1; round <= 5; ++round) {
        cout << "\n======= CYCLE " << round << " =======\n";

        string reason;
        int priorityLane = selectPriorityLane(lanes, reason);

        for (auto& lane : lanes) {
            lane.isGreen = (lane.id == priorityLane);

            if (lane.isGreen) {
                int passed = min(5 + rand() % 3, lane.vehicleCount); // 5–7 vehicles pass
                lane.vehicleCount -= passed;
                lane.waitTime = 0;
            } else {
                lane.waitTime += 5;
                lane.vehicleCount += rand() % 3; // Random vehicle generation
            }
        }

        // Show before clearing priority flags
        displayStatus(lanes, priorityLane, reason);

        // Reset priority flags AFTER display
        lanes[priorityLane].hasVIP = false;
        lanes[priorityLane].hasAmbulance = false;
        lanes[priorityLane].hasFiretruck = false;
        this_thread::sleep_for(chrono::seconds(5));
    }

    cout << "\nSimulation complete. Log saved to traffic_log.txt.\n";
    return 0;
}
