#pragma once

enum class Alignment {VERTICAL, HORIZONTAL};
enum class Direction {UP = 1, RIGHT = 2, DOWN = -1, LEFT = -2, NONE = 0};

struct Shift {
    int y;
    int x;
};

Shift GetShift(Direction);
Direction GetDirection(Shift);
Direction ReverseDirection(Direction dir);

struct Cell {
    static const int width = 100;

    int y;
    int x;
    bool operator==(const Cell&) const;
    bool operator!=(const Cell&) const;
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
    void reverse();
    Cell GetCell() const;
};

class PositionOwner {
public:
    virtual Position GetPosition() = 0;
};
