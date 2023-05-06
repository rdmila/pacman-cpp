#pragma once
#include "mobs.h"
#include <string>
#include <array>
#include "view.h"
#include "../controller/controller.h"

class ConsoleLogger;
class SFMLDrawer;
class Controller;

class Model {
    bool finish;
    Map map;
    Pacman pacman;
    std::array<Ghost*, 5> ghosts;
    const static int CELL_WIDTH = Cell::width;

public:
    Model();
    ~Model();

    bool IsFinished();
    void Update();

    friend ConsoleLogger;
    friend SFMLDrawer;
    friend Controller;
};
