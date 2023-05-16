#include "model/mobs.h"
#include "model/model.h"

Model::Model() : finish(false), pacman(map), ghosts() {
    map.load();
    pacman.Init();
    for (auto &i : ghosts) {
        i = std::make_unique<Ghost>(map, pacman);
        i->Init();
    }
    map.EventManager<GameOver>::AddObserver(this);
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
