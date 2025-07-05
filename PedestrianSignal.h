#ifndef PEDESTRIAN_SIGNAL_H
#define PEDESTRIAN_SIGNAL_H

#include <mutex>

enum PedSignalState { DONT_WALK, WALK };

class PedestrianSignal {
private:
    PedSignalState state;
    std::mutex mtx;
    int laneId;

public:
    PedestrianSignal(int id);
    void setState(PedSignalState newState);
    PedSignalState getState();
    void displayState();
};

#endif