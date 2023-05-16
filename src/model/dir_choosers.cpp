#include "model/dir_choosers.h"
#include <cstdlib>
#include <iostream>

ChaseDirectionChooser::ChaseDirectionChooser(PositionOwner& hunter, PositionOwner& aim, Map& map)
        : hunter(hunter), aim(aim), map(map) {}

Direction ChaseDirectionChooser::ChooseDirection() {
    Cell hunter_cell = hunter.GetPosition().GetCell();
    Cell aim_cell = aim.GetPosition().GetCell();
    std::vector<Direction> reversed_path = map.GetShortestPath(hunter_cell, aim_cell);
    return reversed_path.empty() ? Direction::RIGHT : reversed_path.back();
}

Direction RandomDirectionChooser::ChooseDirection() {
    int dir = std::rand() % 4 - 2;
    if (dir >= 0) {
        ++dir;
    }
    return static_cast<Direction>(dir);
}

void PlayerDirectionChooser::SetDesiredDirection(Direction desiredDirection) {
    desired_direction = desiredDirection;
}

PlayerDirectionChooser::PlayerDirectionChooser(): desired_direction(Direction::RIGHT) {}

Direction PlayerDirectionChooser::ChooseDirection() {
    return desired_direction;
}
