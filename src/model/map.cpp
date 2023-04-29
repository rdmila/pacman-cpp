#include <map.h>
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

void Map::InitializeWall(int y, int x, bool is_passage_cell) {
    is_passage[y][x] = is_passage_cell;
}

Map::Map(int height, int width) : is_passage(boost::extents[height][width]) {}

bool Map::IsPassage(const Cell& cell) {
    return is_passage[cell.y][cell.x];
}

bool Map::IsLegalDirection(Cell cell, Direction dir) {
    cell += GetShift(dir);
    return IsPassage(cell);
}
