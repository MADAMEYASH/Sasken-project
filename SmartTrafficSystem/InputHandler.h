#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "Lane.h"
#include <vector>
#include <atomic>

class InputHandler {
public:
    std::vector<Lane> getLaneInputs();
    void run(std::vector<Lane>& lanes, std::atomic<bool>& running);
};

#endif
