#pragma once

#include "model/model.h"
#include "view/view.h"
#include <chrono>

using namespace std::chrono_literals;

class Game {
    using clock_type = std::chrono::steady_clock;
    constexpr static std::chrono::nanoseconds update_interval = 17'000'000ns;

    std::chrono::time_point<clock_type> last_run_time;
    Model model;
    ConsoleLogger logger;

public:
    Game();

    void run();
};
