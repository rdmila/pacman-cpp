#include "view+controller/view.h"
#include <iostream>
#include <string>

View::View(Model &model) : model(model) {}

ConsoleLogger::ConsoleLogger(Model &model) : View(model) {}

void ConsoleLogger::update() {
    Position pacman_pos = model.pacman.GetPosition();
    std::cout << "Pacman position: " << pacman_pos.edge.first.x << " " << pacman_pos.edge.first.y << std::endl;
    int i = 0;
    for (auto &g: model.ghosts) {
        Position pos = g->GetPosition();
        std::cout << "Ghost " << i << " position: " << pos.edge.first.x << " " << pos.edge.first.y << std::endl;
        ++i;
    }
}

sf::Vector2f SFMLDrawer::CellToVector(const Cell &cell) const {
    auto x = static_cast<float>(cell.x);
    auto y = static_cast<float>(cell.y);
    return {x * pixels_for_cell, y * pixels_for_cell};
}

sf::Vector2f SFMLDrawer::PosToVector(const Position &pos) {
    auto first = CellToVector(pos.edge.first);
    auto second = CellToVector(pos.edge.second);
    auto dif = second - first;
    float scale = static_cast<float>(pos.shift) / static_cast<float>(Edge::length);
    return first + dif * scale;
}

SFMLDrawer::SFMLDrawer(Model &model) :
        View(model),
        pixels_for_cell(window_height / static_cast<float>(model.map.GetHeight())),
        ghosts(model.ghosts.size()),
        maze_height(model.map.GetHeight()),
        maze_width(model.map.GetWidth()) {
    window_width = pixels_for_cell * maze_width;
    window.create(sf::VideoMode(window_width, window_height), "Pac-Man");
    window.setFramerateLimit(30);

    pacman.setRadius(pixels_for_cell / 2);
    pacman.setFillColor(sf::Color::Yellow);

    for (int i = 0; i < model.ghosts.size(); ++i) {
        ghosts[i].setRadius(pixels_for_cell / 2);
        ghosts[i].setFillColor(sf::Color::Red);
    }

    boost::multi_array<sf::RectangleShape, 2>::extent_gen extents;
    maze.resize(extents[maze_height][maze_width]);
    for (int i = 0; i < maze_height; ++i) {
        for (int j = 0; j < maze_width; ++j) {
            maze[i][j].setSize(sf::Vector2f(pixels_for_cell, pixels_for_cell));
            maze[i][j].setPosition(j * pixels_for_cell, i * pixels_for_cell);
            window.draw(maze[i][j]);
            sf::Color cell_color = model.map.IsPassage({i, j}) ? sf::Color::Blue : sf::Color::Green;
            maze[i][j].setFillColor(cell_color);
        }
    }
}

void SFMLDrawer::update() {
    auto pacman_coords = PosToVector(model.pacman.GetPosition());
    pacman.setPosition(pacman_coords);
    std::string title = "Lives left: " + std::to_string(model.pacman.GetLives());
    window.setTitle(title);
    window.clear();
    for (const auto &row: maze) {
        for (auto &cell: row) {
            window.draw(cell);
        }
    }
    for (int i = 0; i < ghosts.size(); ++i) {
        auto coords = PosToVector(model.ghosts[i]->GetPosition());
        ghosts[i].setPosition(coords);
        window.draw(ghosts[i]);
    }
    window.draw(pacman);
    window.display();
}

sf::RenderWindow &SFMLDrawer::GetWindow() {
    return window;
}

void SFMLDrawer::GameOver() {
    window.clear(sf::Color::Red);
    window.setFramerateLimit(1);
    window.display();
}
