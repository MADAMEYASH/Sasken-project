#ifndef LANE_H
#define LANE_H

#include <mutex>

class Lane {
public:
    int id;
    int vehicleCount;
    bool hasVIP;
    bool hasPedestrian;
    bool hasAmbulance;
    bool isGreen;
    int waitTime;
    std::mutex mtx;

    Lane(int i);
    void update(int count, bool vip, bool ped, bool amb);

    void setGreen();
    void setRed();
    void setYellow();
    void printStatus();
    
};

#endif
