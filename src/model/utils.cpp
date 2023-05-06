#include "utils.h"
#include <utility>
#include <stdexcept>

Shift GetShift(Direction direction) {
    switch(direction) {
        case Direction::NONE:
            return {0, 0};
        case Direction::UP:
            return {-1, 0};
        case Direction::RIGHT:
            return {0, 1};
        case Direction::DOWN:
            return {1, 0};
        case Direction::LEFT:
            return {0, -1};
        default:
            throw std::invalid_argument("Unknown Direction");
    }
}

Direction GetDirection(Shift shift) {
    if (shift.x == 0) {
        if (shift.y == 0) {
            return Direction::NONE;
        } else if (shift.y > 0) {
            return Direction::DOWN;
        } else {
            return Direction::UP;
        }
    } else if (shift.y != 0) {
        throw std::invalid_argument("Shift is illegal: expected to be parallel to OX or OY");
    } else if (shift.x > 0) {
        return Direction::RIGHT;
    } else {
        return Direction::LEFT;
    }
}

Direction ReverseDirection(Direction dir) {
    int dir_id = static_cast<int>(dir);
    dir_id = -dir_id;
    return Direction(dir_id);
}

Cell& Cell::operator+=(const Shift& shift) {
    y += shift.y;
    x += shift.x;
    return *this;
}

bool Cell::operator==(const Cell& other) const {
    return x == other.x && y == other.y;
}

bool Cell::operator!=(const Cell& other) const {
    return !(*this == other);
}

Shift operator-(const Cell& first, const Cell& second) {
    return {first.y - second.y, first.x - second.x};
}

void Position::reverse() {
    std::swap(edge.first, edge.second);
    shift = Edge::length - shift;
}

Cell Position::GetCell() const {
    return shift * 2 <= Edge::length ? edge.first : edge.second;
}
