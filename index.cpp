#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <random>

using namespace std;

// ANSI color codes
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

struct Lane {
    int id;
    int VC;
    int vehicleCount;
    bool hasVIP;
    bool isGreen;
    bool isYellow;
    int waitTime;
    int incidentType;
    bool hasFiretruck;
    bool hasAmbulance;

    Lane(int id) : id(id), vehicleCount(0), hasVIP(false), hasFiretruck(false),
                   hasAmbulance(false), incidentType(0), isGreen(false), isYellow(false), waitTime(0) {}
};

vector<string> weather = { "Sunny", "Cloudy", "Windy", "Rainy", "Stormy", "Snowy", "Foggy" };
string Incident[4] = {"   No   ", "Accident", "Road Work", "Police"};

string today_weather(){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, weather.size() - 1);
    return weather[dist(gen)];
}

int Conditions(){
    int ch;
    cout << "Is there any Incident at this lane:\n";
    cout << "1. Accident\n2. Road Work\n3. Police Chase\n4. No\n";
    cin >> ch;
    if (ch >= 1 && ch <= 3) return ch;
    return 0;
}

void displayStatus(const vector<Lane>& lanes, int priorityLane, const string& reason, const string& weatherToday,int passed,int entered) {
#if defined(_WIN32) || defined(_WIN64)
    system("CLS");
#else
    system("clear");
#endif

    int intensity = 0;
    for(int i = 0; i < weather.size(); i++) {
        if(weatherToday == weather[i]) {
            intensity = i + 1;
            break;
        }
    }

    cout << "Today's Weather: " << weatherToday << "\n";
    cout << "+--------+------------+-------------+-----------+----------------------+----------+-----------+--------+---------+\n";
    cout << "| Lane   | Vehicles   | Light       | Intensity | Priority Reason      | WaitTime |  Incident | Passed | Entered |\n";
    cout << "+--------+------------+-------------+-----------+----------------------+----------+-----------+--------+---------+\n";

    for (const auto& lane : lanes) {
        cout << "| Lane " << lane.id + 1 << " |     " << lane.vehicleCount << "     |  ";

        if (lane.isGreen)
            cout << GREEN << "GREEN      " << RESET;
        else if (lane.isYellow)
            cout << YELLOW << "YELLOW     " << RESET;
        else
            cout << RED << "RED [WALK] " << RESET;

        cout << " |     " << intensity << "     | ";

        if (lane.id == priorityLane)
            cout << reason;
        else if (lane.hasAmbulance)       cout << "      Ambulance      ";
        else if (lane.hasVIP)             cout << "         VIP         ";
        else if (lane.hasFiretruck)       cout << "     Firetruck       ";
        else                              cout << "                    ";

        cout << " |    " << lane.waitTime << "s    | " << Incident[lane.incidentType]<<"|      "<<(lane.isGreen ? to_string(passed) : "-") << " |        "<< (lane.isGreen ? to_string(entered) : "-")<< " |\n";
    }

    cout << "+--------+------------+-------------+-----------+----------------------+----------+-----------+--------+---------+\n";
}

int selectPriorityLane(vector<Lane>& lanes, string &reason) {
    for (const auto& lane : lanes) {
        if (lane.hasAmbulance) {
            reason = "      Ambulance     ";
            return lane.id;
        }
    }
    for (const auto& lane : lanes) {
        if (lane.hasFiretruck) {
            reason = "      Firetruck      ";
            return lane.id;
        }
    }
    for (const auto& lane : lanes) {
        if (lane.hasVIP) {
            reason = "         VIP         ";
            return lane.id;
        }
    }
    int maxLane = 0, maxCount = lanes[0].vehicleCount;
    for (const auto& lane : lanes) {
        if (lane.vehicleCount > maxCount) {
            maxCount = lane.vehicleCount;
            maxLane = lane.id;
        }
    }
    reason = "    Most vehicles   ";
    return maxLane;
}

int main() {
    int numLanes;
    int passed = 0;
    int entered = 0;
    cout << "Enter number of traffic lanes: ";
    cin >> numLanes;

    vector<Lane> lanes;
    for (int i = 0; i < numLanes; ++i) {
        Lane lane(i);
        char vip, amb;

        cout << "Is there a [ VIP ] at Lane " << i + 1 << "? (y/n): ";
        cin >> vip;
        lane.hasVIP = (vip == 'y' || vip == 'Y');

        if (!lane.hasVIP) {
            cout << "Vehicle count for Lane " << i + 1 << ": ";
            lane.VC = lane.vehicleCount = rand() % 30 + 5;
            cout << lane.VC << endl;
        }

        cout << "Ambulance at Lane " << i + 1 << "? (y/n): ";
        cin >> amb;
        lane.hasAmbulance = (amb == 'y' || amb == 'Y');

        cout << "Firetruck at Lane " << i + 1 << "? (y/n): ";
        cin >> amb;
        lane.hasFiretruck = (amb == 'y' || amb == 'Y');

        lane.incidentType = Conditions();
        lanes.push_back(lane);
    }

    string weatherToday = today_weather();

    while (true) {
        // Check if all lanes are cleared
        bool allClear = true;
        for (const auto& lane : lanes) {
            if (lane.vehicleCount > 0) {
                allClear = false;
                break;
            }
        }

        // if (allClear) {
        //     displayStatus(lanes, -1, "      All Clear!      ", weatherToday);
        //     cout << "\n✅ All lanes are clear. Simulation complete!\n";
        //     break;
        // }
passed = 0;
entered = 0;

for (auto& lane : lanes) {
    if (lane.isGreen) {
        passed = min(5 + rand() % 3, lane.vehicleCount);
        entered = rand() % 3;
        lane.vehicleCount = lane.vehicleCount - passed + entered;
        lane.waitTime = 0;
    } else if (lane.incidentType > 0) {
        lane.waitTime += 7;
        lane.vehicleCount += rand() % 3;
    } else {
        lane.waitTime += 5;
        lane.vehicleCount += rand() % 3;
    }
}

        
        for (auto& lane : lanes) {
            lane.isGreen = false;
            lane.isYellow = false;
        }

        string reason;
        int priorityLane = selectPriorityLane(lanes, reason);

        lanes[priorityLane].isYellow = true;
        displayStatus(lanes, priorityLane, reason, weatherToday,passed,entered);
        this_thread::sleep_for(chrono::seconds(2));

        lanes[priorityLane].isYellow = false;
        lanes[priorityLane].isGreen = true;


        displayStatus(lanes, priorityLane, reason, weatherToday,passed,entered);

        lanes[priorityLane].hasVIP = false;
        lanes[priorityLane].hasAmbulance = false;
        lanes[priorityLane].hasFiretruck = false;

        this_thread::sleep_for(chrono::seconds(4));
    }

    return 0;
}
