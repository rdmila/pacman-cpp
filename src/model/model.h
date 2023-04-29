#pragma once
#include "mobs.h"
#include <array>

class Model {
    bool finish;
    Pacman pacman;
    std::array<Ghost, 5> ghosts;

public:
    Model();

    bool IsFinished();
    void Update();
};