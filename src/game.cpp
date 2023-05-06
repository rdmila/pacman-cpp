#include "game.h"
#include <chrono>
#include <ratio>

#include <iostream>

Game::Game() : model(), logger(model), drawer(model), controller(model, drawer.GetWindow()) {
}

void Game::run() {
    while (true) {
        controller.Update();
        model.Update();
        if (model.IsFinished()) {
            return;
        }
        drawer.update();
    }
}
