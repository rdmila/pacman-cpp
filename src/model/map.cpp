#include "map.h"
#include <stdexcept>

inline Shift GetShift(Direction direction) {
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

Cell& Cell::operator+=(const Shift& shift) {
    y += shift.y;
    x += shift.x;
    return *this;
}

void Map::SetCell(int y, int x, bool is_passage_cell) {
    is_passage[y][x] = is_passage_cell;
}

bool Map::IsPassage(const Cell& cell) {
    return is_passage[cell.y][cell.x];
}

bool Map::IsLegalDirection(Cell cell, Direction dir) {
    cell += GetShift(dir);
    return IsPassage(cell);
}

Position Map::GetPosition(const Cell& first) {
    for (int dir_int = 0; ; ++dir_int) {
        auto dir = static_cast<Direction>(dir_int);
        if (dir == Direction::NONE) {
            break;
        }
        if (IsLegalDirection(first, dir)) {
            Cell second = first;
            second += GetShift(dir);
            return {{first, second}, 0};
        }
    }
}

void Map::SetSize(int height, int width) {
    (*this).height = height;
    (*this).width = width;
    boost::multi_array<bool, 2>::extent_gen extents;
    is_passage.resize(extents[height][width]);
}
