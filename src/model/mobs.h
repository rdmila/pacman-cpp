#pragma once
#include <map.h>
#include "utils.h"
#include "dir_choosers.h"

class Mob : public PositionOwner, public Observer<GhostCollision> {
protected:
    Position position;
    Direction direction;
    int speed;
    DirectionChooser* tmp_chooser;
    Map& map;
    virtual void HandleEvent(GhostCollision) override;
    virtual Cell SpawnCell() = 0;
    virtual void SetChooser() = 0;
    virtual bool EdgeDirectionReverseAllowed() = 0;

public:
    explicit Mob(Map&);
    void Init();

    virtual void UpdatePosition();
    Position GetPosition() override;
};

class Pacman : public Mob {
private:
    int score;
    int lives;
protected:
    Cell SpawnCell() override;
    void SetChooser() override;
    bool EdgeDirectionReverseAllowed() override;
public:
    void HandleEvent(GhostCollision) override;
    PlayerDirectionChooser* GetChooser();
    explicit Pacman(Map&);
    int GetLives() const;
};

class Ghost : public Mob {
    static const int SIGHT_RADIUS = 4 * Cell::width;
    
    int sight_radius_sqr;
    PositionOwner& aim;
    DirectionChooser* chase;
    DirectionChooser& rand;

    Cell SpawnCell() override;
    void SetChooser() override;
    bool EdgeDirectionReverseAllowed() override;
public:
    void UpdatePosition() override;
    Ghost(Map &map, PositionOwner &pacman);
};
