#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


#include <SFML/Graphics.hpp>

#include "Player.h"

class GameManager {
    sf::RenderWindow window = sf::RenderWindow(
        sf::VideoMode({1280u, 720u}),
        "Dondola Game");

    sf::Vector2f cameraPosition = {0, 0};
    sf::Vector2f cameraVelocity = {0, 0};

    sf::Clock clock_;
    sf::Time lastUpdate;

    static constexpr uint32_t sceneCount = 3;
    uint32_t curScene = 1;

    Player *player;

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

    // Main
    void update();

    void render();

    // Title
    void titleUpdate();

    void titleRender();

    // Game Over
    void overUpdate();

    void overRender();

    void (GameManager::*updates[sceneCount])(){titleUpdate, update, overUpdate};

    void (GameManager::*renders[sceneCount])(){titleRender, render, overRender};

public:
    GameManager();

    ~GameManager();


    void goToScene(uint32_t scene);

    void runCurrentScene();
};


#endif //GAMEMANAGER_H
