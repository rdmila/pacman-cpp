#include "utils.h"
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

Cell& Cell::operator+=(const Shift& shift) {
    y += shift.y;
    x += shift.x;
    return *this;
}

Shift operator-(const Cell& first, const Cell& second) {
    return {first.y - second.y, first.x - second.x};
}
