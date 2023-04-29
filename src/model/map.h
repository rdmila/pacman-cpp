#pragma once
#include <array>
#include "loader.h"
#include <boost/multi_array.hpp>

enum class Alignment {VERTICAL, HORIZONTAL};
enum class Direction {UP = 0, RIGHT, DOWN, LEFT, NONE};

class Loader;

struct Shift {
    int y;
    int x;
};

struct Cell {
    int y;
    int x;
    Cell& operator+=(const Shift&);
};

struct Edge {
    static const int length;

    Cell first;
    Cell second;

    // Alignment getAlignment();
};

struct Position {
    Edge edge;
    int shift;
};

class Map {
    int candy_cnt;
    int height;
    int width;
    boost::multi_array<bool, 2> is_passage;
    void SetSize(int height, int width);
    void SetCell(int y, int x, bool is_passage_cell);

public:
    bool IsPassage(const Cell& cell);
    bool IsLegalDirection(Cell cell, Direction direction);
    Position GetPosition(const Cell&);

    friend Loader;
};
