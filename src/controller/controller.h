#pragma once
#include <SFML/Graphics.hpp>
#include "../model/dir_choosers.h"
#include "../model/model.h"

class Model;

class Controller {
    Model& model;
    PlayerDirectionChooser* pacman_chooser;
    sf::RenderWindow& window;
public:
    Controller(Model &model, sf::RenderWindow &window);
    void Update();
};