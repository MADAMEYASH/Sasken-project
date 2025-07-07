#ifndef LOGGER_H
#define LOGGER_H

#include "Lane.h"
#include <vector>

class Logger {
public:
    static void logStatus(const std::vector<Lane>& lanes);
};

#endif
