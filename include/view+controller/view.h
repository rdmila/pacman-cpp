#pragma once
#include "../model/model.h"
#include <SFML/Graphics.hpp>
#include <boost/multi_array.hpp>

class Model;

class View {
protected:
     Model& model;
public:
    explicit View(Model&);
    virtual void update() = 0;
};

class ConsoleLogger : public View {
public:
    explicit ConsoleLogger(Model&);
    void update() override;
};

class SFMLDrawer : public View {
    int window_width;
    int window_height = 800.;
    const float pixels_for_cell;
    int maze_height;
    int maze_width;
    sf::RenderWindow window;
    sf::CircleShape pacman;
    std::vector<sf::CircleShape> ghosts;
    boost::multi_array<sf::RectangleShape, 2> maze;

    sf::Vector2f CellToVector(const Cell& cell) const;
    sf::Vector2f PosToVector(const Position& pos);
//    sf::CircleShape
public:
    explicit SFMLDrawer(Model&);
    void update() override;
    void GameOver();
    sf::RenderWindow &GetWindow();
};
