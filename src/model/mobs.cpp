#include "mobs.h"

Mob::Mob(Map &map) : map(map), speed(10) {}

void Mob::Init() {
    Cell cell = SpawnCell();
    position = map.GetPosition(cell);
    Shift shift = position.edge.second - position.edge.first;
    direction = GetDirection(shift);
    SetChooser();
}

Cell Pacman::SpawnCell() {
    return {18, 6};
}

bool Pacman::EdgeDirectionReverseAllowed() {
    return true;
}

Cell Ghost::SpawnCell() {
    return {1, 2};
}

bool Ghost::EdgeDirectionReverseAllowed() {
    return false;
}

void Mob::UpdatePosition() {
    int run_limit = speed;
    while (run_limit != 0) {
        int to_vertex = Edge::length - position.shift;
        if (to_vertex == 0) {
            auto wanted_dir = tmp_chooser->ChooseDirection();
            Cell cell = position.edge.second;
            if (map.IsLegalDirection(cell, wanted_dir)) {
                direction = wanted_dir;
            } else if (!map.IsLegalDirection(cell, direction)) {
                break;
            }
            Cell first = position.edge.second;
            Cell second = first;
            second += GetShift(direction);
            position = {{first, second}, 0};
        } else {
            if (EdgeDirectionReverseAllowed()) {
                auto wanted_dir = tmp_chooser->ChooseDirection();
                if (static_cast<int>(wanted_dir) == -static_cast<int>(direction)) {
                    direction = wanted_dir;
                    position.reverse();
                    to_vertex = Edge::length - position.shift;
                }
            }
             if (run_limit <= to_vertex) {
                position.shift += run_limit;
                run_limit = 0;
            } else {
                run_limit -= to_vertex;
                position.shift += to_vertex;
            }
        }
    }
}

Position Mob::GetPosition() {
    return position;
}

void Ghost::UpdatePosition() {
    int dist_to_aim_sqr = map.GetStraightDistanceSqr(position.GetCell(), aim.GetPosition().GetCell());
    tmp_chooser = (dist_to_aim_sqr <= sight_radius_sqr ? chase : &rand);
    Mob::UpdatePosition();
}

Pacman::Pacman(Map &map) : Mob(map) {
}

void Pacman::SetChooser() {
    tmp_chooser = new PlayerDirectionChooser();
}

PlayerDirectionChooser *Pacman::GetChooser() {
    return dynamic_cast<PlayerDirectionChooser*>(tmp_chooser);
}

void Ghost::SetChooser() {
    tmp_chooser = &rand;
}

Ghost::Ghost(Map &map, PositionOwner &pacman)
        : Mob(map),
          aim(pacman),
          sight_radius_sqr(SIGHT_RADIUS * SIGHT_RADIUS),
          chase(new ChaseDirectionChooser(*this, pacman, map)),
          rand(RandomDirectionChooser::GetInstance()) {
}
