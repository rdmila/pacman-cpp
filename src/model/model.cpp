#include "mobs.h"
#include "model.h"

Model::Model(): finish(false) {}

bool Model::IsFinished() {
    return finish;
}

void Model::Update() {
    pacman.UpdatePosition();
    for (auto &ghost : ghosts) {
        ghost.UpdatePosition();
    }
}
