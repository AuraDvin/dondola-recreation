//
// Created by Edvin on 23. 01. 25.
//

#ifndef PLAYER_H
#define PLAYER_H
#include <cstdint>
#include <iostream>

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"


class Player {
    uint32_t health = 3;
    sf::Vector2f position;
    sf::Texture *texture_;
    sf::RenderWindow *window;
    sf::Sprite *sprite_;

public:
    explicit Player(sf::RenderWindow &window, const std::string texturePath) {
        this->window = &window;
        position = {window.getSize().x / 2.f, window.getSize().y / 2.f};
        texture_ = new sf::Texture(texturePath, false);
        sprite_ = new sf::Sprite(*texture_);
    }


    void render() {
        sprite_->setPosition(position);
        window->draw(*sprite_);
    }

    void update(int32_t dt) {
        std::cout << "New delta time: " << dt << std::endl;
        while (const std::optional<sf::Event> ev = window->pollEvent()) {
            sf::Event event = ev.value();
            if (event.is<sf::Event::Closed>()) window->close();

        }
    }
};


#endif //PLAYER_H
