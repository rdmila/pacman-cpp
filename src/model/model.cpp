#include "../../include/model/mobs.h"
#include "../../include/model/model.h"
#include "../../include/model/loader.h"

Model::Model() : finish(false), pacman(map), ghosts() {
    Loader::Load(map);
    pacman.Init();
    for (auto &i : ghosts) {
        i = new Ghost(map, pacman);
        i->Init();
    }
    map.EventManager<GameOver>::AddObserver(this);
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

void Model::HandleEvent(GameOver event) {
    finish = true;
}
