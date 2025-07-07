#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Lane.h"
#include <vector>
#include <atomic>

class Controller {
    std::vector<Lane>& lanes;
public:
    Controller(std::vector<Lane>& l);
    void run(std::atomic<bool>& running);
};

#endif
