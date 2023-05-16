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

Cell operator+(const Cell& first, const Shift& second) {
    Cell res = first;
    res += second;
    return res;
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

Cell::Cell(int y, int x): y(y), x(x) {}

Shift operator-(const Cell& first, const Cell& second) {
    return {first.y - second.y, first.x - second.x};
}

Point& Point::operator-=(const Point& other) {
    y -= other.y;
    x -= other.x;
    return *this;
}

Point& Point::operator+=(const Point& other) {
    y += other.y;
    x += other.x;
    return *this;
}

Point& Point::operator*=(float scale) {
    y *= scale;
    x *= scale;
    return *this;
}

Point& Point::operator/=(float scale) {
    y /= scale;
    x /= scale;
    return *this;
}

Point Point::operator*(float scale) const {
    Point res = *this;
    res *= scale;
    return res;
}

Point Point::operator/(float scale) const {
    Point res = *this;
    res /= scale;
    return res;
}

float Point::magnitude_sqr() const {
    return y * y + x * x;
}

Point operator-(const Point& first, const Point& second) {
    Point res = first;
    res -= second;
    return res;
}

Point operator+(const Point& first, const Point& second) {
    Point res = first;
    res += second;
    return res;
}

void Position::reverse() {
    std::swap(edge.from, edge.to);
    shift = Edge::length - shift;
}

Cell Position::GetCell() const {
    return shift * 2 <= Edge::length ? edge.from : edge.to;
}

Position::Position(Cell from, Direction direction): edge(from, direction), shift(0) {}

Position::Position(Edge edge, int shift): edge(edge), shift(shift) {}

Point PositionOnCanvas(const Cell& cell) {
    return {static_cast<float>(cell.y * Cell::width), static_cast<float>(cell.x * Cell::width)};
}

Point PositionOnCanvas(const Position &pos) {
    Point src_point = PositionOnCanvas(pos.edge.from);
    Point dst_point = PositionOnCanvas(pos.edge.to);
    Point shift = (dst_point - src_point) * (static_cast<float>(pos.shift) / Edge::length);
    Point res = src_point + shift;
    return res;
}

Edge::Edge(Cell from, Cell to): from(from), to(to) {}

Edge::Edge(Cell from, Direction direction): from(from), to(from + GetShift(direction)) {}
