#pragma once

#include <array>
#include <boost/multi_array.hpp>
#include "utils.h"

class Map : public EventManager<GhostCollision>,
            public EventManager<GameOver> {
    size_t candy_cnt;
    size_t height;
    size_t width;
    boost::multi_array<bool, 2> is_passage;

    void SetSize(size_t height_, size_t width_);
    void SetCell(size_t y, size_t x, bool is_passage_cell);

public:
    void load();
    bool IsPassage(const Cell &cell);
    bool IsLegalDirection(Cell cell, Direction direction);
    [[nodiscard]] size_t GetHeight() const;
    [[nodiscard]] size_t GetWidth() const;

    int GetStraightDistanceSqr(Cell from, Cell to);
    std::vector<Direction> GetShortestPath(Cell from, Cell to);
};
