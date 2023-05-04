#pragma once

#include "model/model.h"
#include "view/view.h"
#include <chrono>

using namespace std::chrono_literals;

class Game {
    using clock_type = std::chrono::steady_clock;
    const static std::chrono::nanoseconds constexpr update_interval = 1'000'000'000ns;

    std::chrono::time_point<clock_type> last_run_time;
    Model model;
    ConsoleLogger logger;

public:
    Game();

    void run();
};
