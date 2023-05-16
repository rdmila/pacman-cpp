#include <SFML/Graphics.hpp>
#include "../../include/view+controller/controller.h"
#include "../../include/model/utils.h"

void Controller::Update() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
            model.finish = true;
        } else if (event.key.code == sf::Keyboard::Left) {
            pacman_chooser->SetDesiredDirection(Direction::LEFT);
        } else if (event.key.code == sf::Keyboard::Right) {
            pacman_chooser->SetDesiredDirection(Direction::RIGHT);
        } else if (event.key.code == sf::Keyboard::Down) {
            pacman_chooser->SetDesiredDirection(Direction::DOWN);
        } else if (event.key.code == sf::Keyboard::Up) {
            pacman_chooser->SetDesiredDirection(Direction::UP);
        }
    }
}

Controller::Controller(Model &model, sf::RenderWindow &window) : model(model), window(window), pacman_chooser(model.pacman.GetChooser()) {}
