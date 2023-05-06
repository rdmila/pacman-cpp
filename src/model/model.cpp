#include "mobs.h"
#include "model.h"
#include "loader.h"

Model::Model() : finish(false), pacman(map) {
    Loader::Load(map);
    pacman.Init();
    for (auto &i : ghosts) {
        i = new Ghost(map, pacman);
        i->Init();
    }
}

Model::~Model() {
    for (auto &i : ghosts) {
        delete i;
    }
}

bool Model::IsFinished() {
    return finish;
}

void Model::Update() {
    pacman.UpdatePosition();
    for (auto &ghost : ghosts) {
        ghost->UpdatePosition();
    }
}

