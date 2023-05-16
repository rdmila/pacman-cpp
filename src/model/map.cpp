#include "model/map.h"
#include <stdexcept>
#include <deque>
#include <fstream>
#include "config.h"

void Map::SetCell(size_t y, size_t x, bool is_passage_cell) {
    is_passage[y][x] = is_passage_cell;
}

bool Map::IsPassage(const Cell& cell) {
    return is_passage[cell.y][cell.x];
}

bool Map::IsLegalDirection(Cell cell, Direction dir) {
    cell += GetShift(dir);
    return IsPassage(cell);
}

void Map::SetSize(size_t height_, size_t width_) {
    height = height_;
    width = width_;
    boost::multi_array<bool, 2>::extent_gen extents;
    is_passage.resize(extents[height][width_]);
}

size_t Map::GetHeight() const {
    return height;
}

size_t Map::GetWidth() const {
    return width;
}

int Map::GetStraightDistanceSqr(Cell from, Cell to) {
    auto shift = to - from;
    shift.x *= Cell::width;
    shift.y *= Cell::width;
    return (shift.x * shift.x + shift.y * shift.y);
}

std::vector<Direction> Map::GetShortestPath(Cell from, Cell to) {
    boost::multi_array<Direction, 2>::extent_gen extents;
    boost::multi_array<Direction, 2> prev_dir(extents[height][width]);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            prev_dir[i][j] = Direction::NONE;
        }
    }

    std::deque<Cell> to_visit(1, from);
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
            if (IsPassage(next) && prev_dir[next.y][next.x] == Direction::NONE && next != from) {
                prev_dir[next.y][next.x] = static_cast<Direction>(i);
                to_visit.push_back(next);
                if (next == to) {
                    break;
                }
            }
        }
    }

    std::vector<Direction> path;
    Cell cell = to;
    while (cell != from) {
        auto dir = prev_dir[cell.y][cell.x];
        path.push_back(dir);
        cell += GetShift(ReverseDirection(dir));
    }
    return path;
}

void Map::load() {
    std::ifstream map_file(MAP_FILE_PATH);
    std::string line;
    std::getline(map_file, line);
    int height_ = std::stoi(line);

    std::getline(map_file, line);
    int width_ = line.length();

    SetSize(height_, width_);
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            SetCell(i, j, (line[j] == '0'));
        }
        std::getline(map_file, line);
    }
}