#pragma once
#include <map.h>

class Mob {
    Position position;
    Direction direction;
    int speed;
    // DirectionChooser& direction_chooser;
    Map& map;

    virtual Cell GetSpawnCell() = 0;
    static Direction GetSpawnDirection();
    static int GetInitialSpeed();

public:
    Mob(Map&);
    void Init();

    void UpdatePosition();
};

class Pacman : public Mob {
    Cell GetSpawnCell();
public:
    Pacman(Map&);
};

class Ghost : public Mob {
    Cell GetSpawnCell();
public:
    void UpdatePosition();
    Ghost(Map&);
};
