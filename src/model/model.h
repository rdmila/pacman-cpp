#pragma once
#include "mobs.h"
#include <string>
#include <array>

class Model {
    bool finish;
    Map map;
    Pacman pacman;
    std::array<Ghost*, 5> ghosts;

public:
    Model();
    ~Model();

    bool IsFinished();
    void Update();
};
