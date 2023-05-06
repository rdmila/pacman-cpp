#pragma once

#include <array>
#include "loader.h"
#include <boost/multi_array.hpp>
#include "utils.h"

class Loader;

class Map
        : public EventManager<GhostCollision>,
          public EventManager<GameOver> {
    int candy_cnt;
    int height;
    int width;
    boost::multi_array<bool, 2> is_passage;

    void SetSize(int height_, int width_);
    void SetCell(int y, int x, bool is_passage_cell);

public:
    bool IsPassage(const Cell &cell);
    bool IsLegalDirection(Cell cell, Direction direction);
    Position GetPosition(const Cell &);
    int GetHeight() const;
    int GetWidth() const;

    friend Loader;
    int GetStraightDistanceSqr(Cell cell, Cell cell1);
    std::vector<Direction> GetShortestPath(Cell cell, Cell cell1);
};
