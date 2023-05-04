#include "view.h"
#include "../model/utils.h"
#include <iostream>

void ConsoleLogger::show() {
    Position pos = model.pacman.GetPosition();
    std::cout << pos.edge.first.x << " " << pos.edge.first.y << std::endl;
//    for (auto &g : model.ghosts) {
//        Position pos = g->GetPosition();
//        std::cout << pos.edge.first.x << " " << pos.edge.first.y << std::endl;
//}
}

View::View(Model& model): model(model) {}

ConsoleLogger::ConsoleLogger(Model& model): View(model) {}

