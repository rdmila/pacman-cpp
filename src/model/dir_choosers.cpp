#include "dir_choosers.h"
#include <cstdlib>
#include <iostream>

ChaseDirectionChooser::ChaseDirectionChooser(PositionOwner& hunter, PositionOwner& aim, Map& map)
        : hunter(hunter), aim(aim), map(map) {}

Direction ChaseDirectionChooser::ChooseDirection() {
    Cell hunter_cell = hunter.GetPosition().GetCell();
    Cell aim_cell = aim.GetPosition().GetCell();
    std::vector<Direction> reversed_path = map.GetShortestPath(hunter_cell, aim_cell);
    return reversed_path.back();
}

RandomDirectionChooser* RandomDirectionChooser::instance = nullptr;

Direction RandomDirectionChooser::ChooseDirection() {
    int dir = std::rand() % 4 - 2;
    if (dir >= 0) {
        ++dir;
    }
    return static_cast<Direction>(dir);
}

RandomDirectionChooser& RandomDirectionChooser::GetInstance() {
    if (instance == nullptr) {
        instance = new RandomDirectionChooser();
    }
    return *instance;
}

void PlayerDirectionChooser::SetDesiredDirection(Direction desiredDirection) {
    desired_direction = desiredDirection;
}

PlayerDirectionChooser::PlayerDirectionChooser(): desired_direction(Direction::LEFT) {}

Direction PlayerDirectionChooser::ChooseDirection() {
    return desired_direction;
}
