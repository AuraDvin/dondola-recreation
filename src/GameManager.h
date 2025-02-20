#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


#include <SFML/Graphics.hpp>

#include "EnemyManager.h"
#include "Player.h"

struct Camera {
    sf::Vector2f position = {0, 0};
    sf::Vector2f velocity = {0, 0};
    const double maxPlayerDistanceSquared = 400.0;
    const double minPlayerDistanceSquared = 200.0;
    const float accelerationRate = 200.f;
    const float decelerationRate = 400.f;
    const float maxSpeed = 300.f;
    const double maxSpeedSquared = std::pow(maxSpeed, 2);
};

class GameManager {
    sf::RenderWindow window = sf::RenderWindow(
        sf::VideoMode({1280u, 720u}),
        "Dondola Game");

    Camera camera_;
    sf::Clock clock_;
    sf::Time lastUpdate;

    static constexpr uint32_t sceneCount = 3;
    uint32_t curScene = 1;

    Player *player;
    EnemyManager *em;

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

    void (GameManager::*updates[sceneCount])(){
        &GameManager::titleUpdate,
        &GameManager::update,
        &GameManager::overUpdate};

    void (GameManager::*renders[sceneCount])(){
        &GameManager::titleRender,
        &GameManager::render,
        &GameManager::overRender
    };

    void updateCamera(float deltaTime);

public:
    GameManager();

    ~GameManager();


    void goToScene(uint32_t scene);

    void runCurrentScene();
};


#endif //GAMEMANAGER_H
