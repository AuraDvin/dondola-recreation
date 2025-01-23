//
// Created by Edvin on 23. 01. 25.
//

#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


#include <SFML/Graphics.hpp>

#include "Player.h"

class GameManager {
    sf::RenderWindow window = sf::RenderWindow(
        sf::VideoMode({1280u, 720u}),
        "Dondola Game");
    Player* player;
    uint32_t scene = 1;
    sf::Clock clock_;
    sf::Time lastUpdate;

public:
    GameManager();
    ~GameManager();

    void update();
    void render();

};


#endif //GAMEMANAGER_H
