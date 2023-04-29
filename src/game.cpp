#include "game.h"
#include <chrono>

// Game::Game(): last_run_time(clock.now) {}

Game::Game() {}

void Game::run() {
    while (true) {
        // auto time_diff = clock.now() - last_run_time;
        // if (time_diff.count() < update_interval) {
            // continue;
        // }
        model.Update();
        if (model.IsFinished()) {
            return;
        }
        logger.show();
    }

}