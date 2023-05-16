#pragma once

#include "mobs.h"
#include <string>
#include <array>
#include "view+controller/view.h"
#include "view+controller/controller.h"

class ConsoleLogger;

class SFMLDrawer;

class Controller;

class Model : Observer<GameOver> {
    bool finish;
    Map map;
    Pacman pacman;
    std::array<Ghost *, 5> ghosts;
    const static int CELL_WIDTH = Cell::width;

public:
    void HandleEvent(GameOver event) override;

    Model();
    ~Model();

    bool IsFinished();
    void Update();

    friend ConsoleLogger;
    friend SFMLDrawer;
    friend Controller;
};
