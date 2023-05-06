#include "view.h"
#include <iostream>

ConsoleLogger::ConsoleLogger(Model &model) : View(model) {}

void ConsoleLogger::update() {
    Position pacman_pos = model.pacman.GetPosition();
    std::cout << pacman_pos.edge.first.x << " " << pacman_pos.edge.first.y << std::endl;
    for (auto &g: model.ghosts) {
        Position pos = g->GetPosition();
        std::cout << pos.edge.first.x << " " << pos.edge.first.y << std::endl;
    }
}

View::View(Model& model): model(model) {}
