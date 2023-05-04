#include "dir_choosers.h"
#include <cstdlib>

ChaseDirectionChooser::ChaseDirectionChooser(PositionOwner& hunter, PositionOwner& aim, Map& map)
        : hunter(hunter), aim(aim), map(map) {}

Direction ChaseDirectionChooser::ChooseDirection() {
//    Cell hunter_cell = hunter.GetPosition().GetCell();
//    Cell aim_cell = aim.GetPosition().GetCell();
//    Path& path = map.GetShortestPath(hunter_cell, aim_cell);
    return Direction::UP; // TODO
}

RandomDirectionChooser* RandomDirectionChooser::instance = nullptr;

Direction RandomDirectionChooser::ChooseDirection() {
    int dir = std::rand() % 4;
    return static_cast<Direction>(dir);
}

RandomDirectionChooser& RandomDirectionChooser::GetInstance() {
    if (instance == nullptr) {
        instance = new RandomDirectionChooser();
    }
    return *instance;
}

//RandomDirectionChooser::RandomDirectionChooser() {}
