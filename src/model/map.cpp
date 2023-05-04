#include "map.h"
#include <stdexcept>

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
    throw std::invalid_argument("Invalid cell: no available directions");
}

void Map::SetSize(int height_, int width_) {
    height = height_;
    width = width_;
    boost::multi_array<bool, 2>::extent_gen extents;
    is_passage.resize(extents[height][width_]);
}
