#include "mobs.h"

Mob::Mob(Map& map): map(map) {}

void Mob::Init() {
    Cell cell = GetSpawnCell();

    position = map.GetPosition(cell);
    direction = GetSpawnDirection();
    speed = GetInitialSpeed();
}

Cell Pacman::GetSpawnCell() {
    return {19, 3};
}

Cell Ghost::GetSpawnCell() {
    return {19, 12};
}

Direction Mob::GetSpawnDirection() {
    return Direction::NONE;
}

int Mob::GetInitialSpeed() {
    return 1;
}

void Mob::UpdatePosition() {
    return;
}

void Ghost::UpdatePosition() {
    Mob::UpdatePosition();
}

Pacman::Pacman(Map& map): Mob(map) {}

Ghost::Ghost(Map& map): Mob(map) {}
