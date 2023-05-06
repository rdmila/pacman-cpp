#include "map.h"
#include <stdexcept>
#include <deque>

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
    for (int dir_int = -2; dir_int <= 2; ++dir_int) {
        auto dir = static_cast<Direction>(dir_int);
        if (dir == Direction::NONE) {
            continue;
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

int Map::GetHeight() const {
    return height;
}

int Map::GetWidth() const {
    return width;
}

int Map::GetStraightDistanceSqr(Cell cell, Cell cell1) {
    auto shift = cell1 - cell;
    shift.x *= Cell::width;
    shift.y *= Cell::width;
    return (shift.x * shift.x + shift.y * shift.y);
}

std::vector<Direction> Map::GetShortestPath(Cell first, Cell second) {
    boost::multi_array<Direction, 2>::extent_gen extents;
    boost::multi_array<Direction, 2> prev_dir(extents[height][width]);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            prev_dir[i][j] = Direction::NONE;
        }
    }

    std::deque<Cell> to_visit(1, first);
    while (!to_visit.empty()) {
        Cell cell = to_visit.front();
        to_visit.pop_front();
        for (int i = -2; i <= 2; ++i) {
            auto dir = static_cast<Direction>(i);
            if (dir == Direction::NONE) {
                continue;
            }
            auto shift = GetShift(dir);
            Cell next = cell;
            next += shift;
            if (IsPassage(next) && prev_dir[next.y][next.x] == Direction::NONE && next != first) {
                prev_dir[next.y][next.x] = static_cast<Direction>(i);
                to_visit.push_back(next);
                if (next == second) {
                    break;
                }
            }
        }
    }

    std::vector<Direction> path;
    Cell cell = second;
    while (cell != first) {
        auto dir = prev_dir[cell.y][cell.x];
        path.push_back(dir);
        cell += GetShift(ReverseDirection(dir));
    }
    return path;
}
