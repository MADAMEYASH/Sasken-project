#include "Controller.h"
#include "InputHandler.h"
#include <thread>
#include <atomic>

int main() {
    InputHandler inputHandler;
    std::vector<Lane> lanes = inputHandler.getLaneInputs();
    Controller controller(lanes);

    std::atomic<bool> running(true);
    std::thread controlThread(&Controller::run, &controller, std::ref(running));

    inputHandler.run(lanes, running);

    running = false;
    controlThread.join();
    return 0;
}
