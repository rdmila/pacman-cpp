#include "model/mobs.h"
#include "constants.h"
#include <iostream>

Mob::Mob(Map &map) : map(map), speed(NORMAL_MOB_SPEED) {}

void Mob::Init() {
    position = SpawnPosition();
    Shift shift = position.edge.to - position.edge.from;
    direction = GetDirection(shift);
    InitChooser();
    map.EventManager<GhostCollision>::AddObserver(this);
}

void Mob::HandleEvent(GhostCollision) {
    position = SpawnPosition();
    Shift shift = position.edge.to - position.edge.from;
    direction = GetDirection(shift);
}

void Pacman::HandleEvent(GhostCollision event) {
    Mob::HandleEvent(event);
    GetChooser().SetDesiredDirection(direction);
    --lives;
    if (lives == 0) {
        map.EventManager<GameOver>::SendEvent(GameOver());
    }
}

Position Pacman::SpawnPosition() {
    return PACMAN_SPAWN_POSITION;
}

bool Pacman::EdgeDirectionReverseAllowed() {
    return true;
}

Position Ghost::SpawnPosition() {
    return GHOST_SPAWN_POSITION;
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
            Cell cell = position.edge.to;
            if (map.IsLegalDirection(cell, wanted_dir)) {
                direction = wanted_dir;
            } else if (!map.IsLegalDirection(cell, direction)) {
                break;
            }
            Cell first = position.edge.to;
            Cell second = first + GetShift(direction);
            position = Position(Edge(first, second), 0);
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
    tmp_chooser = (dist_to_aim_sqr <= sight_radius_sqr ? chase : rand);
    Mob::UpdatePosition();
    auto ghost_pos = PositionOnCanvas(position);
    auto pacman_pos = PositionOnCanvas(aim.GetPosition());
    float dist_sqr = (ghost_pos - pacman_pos).magnitude_sqr();
    float limit = Edge::length / 2.;
    if (dist_sqr <= limit * limit) {
        map.EventManager<GhostCollision>::SendEvent(GhostCollision());
    }
}

Pacman::Pacman(Map &map) : Mob(map), score(0), lives(2) {
}

void Pacman::InitChooser() {
    tmp_chooser = std::make_shared<PlayerDirectionChooser>();
}

PlayerDirectionChooser& Pacman::GetChooser() {
    return dynamic_cast<PlayerDirectionChooser&>(*tmp_chooser);
}

int Pacman::GetLives() const {
    return lives;
}

void Ghost::InitChooser() {
    tmp_chooser = rand;
}

Ghost::Ghost(Map &map, PositionOwner &pacman)
        : Mob(map),

          aim(pacman),
          sight_radius_sqr(SIGHT_RADIUS * SIGHT_RADIUS),
          chase(std::make_shared<ChaseDirectionChooser>(*this, pacman, map)),
          rand(std::make_shared<RandomDirectionChooser>()) {
}