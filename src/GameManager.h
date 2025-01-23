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

    sf::Clock clock_;
    sf::Time lastUpdate;

    static constexpr uint32_t sceneCount = 3;
    uint32_t curScene = 1;

    Player* player;

    //TODO:
    /*
     * Scenes functionality
     * I.E. when rendering and updating it will use the methods in a
     * chosen scene:
     * -> title should only render text and buttons
     * -> Main screen should render health, enemies and the player
     * -> Game over screen should render text and buttons
     *
     */
public:
    GameManager();
    ~GameManager();

    void (GameManager::*updates[sceneCount])();
    void (GameManager::*renders[sceneCount])();

    void update();
    void render();
    void goToScene(uint32_t scene);
    void runCurrentScene();
};


#endif //GAMEMANAGER_H
