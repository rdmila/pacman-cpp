#include "view.h"
#include <iostream>

ConsoleLogger::ConsoleLogger(Model &model) : View(model) {}

void ConsoleLogger::update() {
    Position pacman_pos = model.pacman.GetPosition();
    std::cout << "Pacman position: " << pacman_pos.edge.first.x << " " << pacman_pos.edge.first.y << std::endl;
    int i = 0;
    for (auto &g: model.ghosts) {
        Position pos = g->GetPosition();
        std::cout << "Ghost " << i << " position: " << pos.edge.first.x << " " << pos.edge.first.y << std::endl;
        ++i;
    }
}

View::View(Model& model): model(model) {}
