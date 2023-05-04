#pragma once

enum class Alignment {VERTICAL, HORIZONTAL};
enum class Direction {UP = 0, RIGHT, DOWN, LEFT, NONE};

struct Shift {
    int y;
    int x;
};

Shift GetShift(Direction);
Direction GetDirection(Shift);

struct Cell {
    static const int width = 100;

    int y;
    int x;
    Cell& operator+=(const Shift&);
};

Shift operator-(const Cell& first, const Cell& second);

struct Edge {
    static const int length = Cell::width;

    Cell first;
    Cell second;

    // Alignment getAlignment();
};

struct Position {
    Edge edge;
    int shift;
};

class PositionOwner {
public:
    virtual Position GetPosition() = 0;
};
