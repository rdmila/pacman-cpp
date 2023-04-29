#pragma once
#include <array>
#include <boost/multi_array.hpp>

enum class Alignment {VERTICAL, HORIZONTAL};
enum class Direction {NONE, UP, RIGHT, DOWN, LEFT};

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
    void InitializeWall(int y, int x, bool is_passage_cell);

public:
    Map(int height, int width);
    bool IsPassage(const Cell& cell);
    bool IsLegalDirection(Cell cell, Direction direction);
};
