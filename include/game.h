#pragma once

#include "model/model.h"
#include "view+controller/view.h"

class Game {
    Model model;
    ConsoleLogger logger;
    SFMLDrawer drawer;
    Controller controller;

public:
    Game();

    void run();
};
