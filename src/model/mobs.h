#pragma once

class Mob {
public:
    void UpdatePosition();
};

class Pacman : public Mob {

};

class Ghost : public Mob {
public:
    void UpdatePosition();
};
