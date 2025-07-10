#ifndef LOGGER_H
#define LOGGER_H

#include "Lane.h"
#include <vector>
#include <string>
#include <fstream>
#include <ctime>

class Logger {
public:
    static void logStatus(const std::vector<Lane>& lanes, int cycle);
};

#endif
