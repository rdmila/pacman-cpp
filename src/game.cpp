#include "game.h"
#include <chrono>
#include <ratio>

#include <iostream>

Game::Game(): model(), logger(model) {
    last_run_time = clock_type::now();
}

void Game::run() {
    while (true) {
     std::chrono::duration<long int, std::nano> time_diff = clock_type::now() - last_run_time;
     if (time_diff.count() < update_interval.count()) {
         continue;
     }
    last_run_time = clock_type::now();
    model.Update();
    if (model.IsFinished()) {
        return;
    }
        logger.show();
    }
}