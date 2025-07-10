#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Lane.h"
#include <vector>
#include <atomic>

class Controller {
private:
    std::vector<Lane>& lanes;
public:
    Controller(std::vector<Lane>& l);
    void run(std::atomic<bool>& running);
    int selectPriorityLane();
};

#endif
