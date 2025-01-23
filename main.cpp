#include <iostream>
#include <SFML/Graphics.hpp>

#include "src/GameManager.h"

int main() {
    GameManager gm;

    /*sf::RenderWindow window(sf::VideoMode({800, 600}), "SFML window");
    window.setFramerateLimit(60);

    while (window.isOpen()) {
        while (const std::optional<sf::Event> ev = window.pollEvent()) {
            sf::Event event = ev.value();
            if (event.is<sf::Event::Closed>()) window.close();
        }

        window.clear(sf::Color::Black);

        window.display();
    }*/
    return 0;
}
