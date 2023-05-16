#include "model/utils.h"
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

Cell& Cell::operator*=(int scale) {
    y *= scale;
    x *= scale;
    return *this;
}

Shift operator-(const Cell& first, const Cell& second) {
    int fir_x = static_cast<int>(first.x);
    int fir_y = static_cast<int>(first.y);
    int sec_x = static_cast<int>(second.x);
    int sec_y = static_cast<int>(second.y);

    return {fir_y - sec_y, fir_x - sec_x};
}

void Position::reverse() {
    std::swap(edge.first, edge.second);
    shift = Edge::length - shift;
}

Cell Position::GetCell() const {
    return shift * 2 <= Edge::length ? edge.first : edge.second;
}

Cell PositionOnCanvas(const Position &pos) {
    auto first = pos.edge.first;
    auto second = pos.edge.second;
    auto dif = second - first;
    first *= Edge::length;
    dif.x *= pos.shift;
    dif.y *= pos.shift;
    first += dif;
    return first;
}