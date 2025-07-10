#include "Controller.h"
#include "InputHandler.h"
#include <thread>
#include <atomic>

int main() {
    std::atomic<bool> running(true);

    InputHandler inputHandler;
    std::vector<Lane> lanes = inputHandler.getLaneInputs();

    Controller controller(lanes);
    std::thread controlThread(&Controller::run, &controller, std::ref(running));

    // No user input; just simulate a fixed duration
    std::this_thread::sleep_for(std::chrono::seconds(30));

    running = false;
    controlThread.join();

    return 0;
}
