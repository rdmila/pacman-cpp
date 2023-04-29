#pragma once
#include "model/model.h"
#include "view/view.h"
#include <chrono>

// using namespace std::chrono_literals;

class Game {
    // const static std::chrono::milliseconds update_interval = 10ms;

    // std::chrono::steady_clock clock;
    // std::chrono::time_point last_run_time;
    Model model;
    ConsoleLogger logger;

public:
    Game();
    void run();
};
