#pragma once
#include "utils.h"
#include "map.h"

class DirectionChooser {
public:
    virtual Direction ChooseDirection() = 0;
};

class RandomDirectionChooser : public DirectionChooser {
    static RandomDirectionChooser* instance;
    RandomDirectionChooser() = default;
    RandomDirectionChooser(const RandomDirectionChooser&) = delete;
public:
    RandomDirectionChooser& operator=(RandomDirectionChooser&) = delete;
    static RandomDirectionChooser& GetInstance();
    Direction ChooseDirection() override;
};

class ChaseDirectionChooser : public DirectionChooser {
    PositionOwner& hunter;
    PositionOwner& aim;
    Map& map;
public:
    ChaseDirectionChooser(PositionOwner& hunter, PositionOwner& aim, Map& map);
    Direction ChooseDirection() override;
};

class PlayerDirectionChooser : public DirectionChooser {
private:
    Direction desired_direction;
public:
    PlayerDirectionChooser();
    Direction ChooseDirection() override;
    void SetDesiredDirection(Direction desiredDirection);
};
