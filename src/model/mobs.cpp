#include "mobs.h"

Mob::Mob(Map &map) : map(map), speed(45) {}

void Mob::Init() {
    Cell cell = SpawnCell();
    position = map.GetPosition(cell);
    Shift shift = position.edge.second - position.edge.first;
    direction = GetDirection(shift);
    SetChooser();
}

Cell Pacman::SpawnCell() {
    return {19, 3};
}

Cell Ghost::SpawnCell() {
    return {19, 12};
}

void Mob::UpdatePosition() {
    int run_limit = speed;
    while (run_limit > 0) {
        int to_vertex = Edge::length - position.shift;
        if (to_vertex == 0) {
            direction = tmp_chooser->ChooseDirection();
            Cell first = position.edge.second;
            Cell second = first;
            second += GetShift(direction);
            position = {{first, second}, 0};
        } else if (run_limit <= to_vertex) {
            position.shift += run_limit;
            run_limit = 0;
        } else {
            run_limit -= to_vertex;
            position.shift += to_vertex;
        }
    }
}

Position Mob::GetPosition() {
    return position;
}

void Ghost::UpdatePosition() {
//    int dist_to_aim = map.GetStraightDistance(position, aim.GetPosition());
//    tmp_chooser = (dist_to_aim <= sight_radius ? chase : &rand);
    Mob::UpdatePosition();
}

Pacman::Pacman(Map &map) : Mob(map) {
}

void Pacman::SetChooser() {
    tmp_chooser = &RandomDirectionChooser::GetInstance();
}

void Ghost::SetChooser() {

    tmp_chooser = &rand;
}

Ghost::Ghost(Map &map, PositionOwner &pacman)
        : Mob(map),
          aim(pacman),
          sight_radius(SIGHT_RADIUS),
          chase(new ChaseDirectionChooser(*this, pacman, map)),
          rand(RandomDirectionChooser::GetInstance()) {
}
