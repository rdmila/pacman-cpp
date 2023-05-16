#include "../include/game.h"

Game::Game() : model(), logger(model), drawer(model), controller(model, drawer.GetWindow()) {
}

void Game::run() {
    while (true) {
        controller.Update();
        model.Update();
        if (model.IsFinished()) {
            drawer.GameOver();
            return;
        }
        drawer.update();
    }
}
