#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H


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

inline bool paused = false;
inline const std::string gameName= "Dondola";

class GameManager {
public:
    GameManager();

    ~GameManager();

    void goToScene(uint32_t sceneIdx);

    void runCurrentScene();

private:
    bool pausePressedOnLastUpdate = false;
    void updateCamera(float deltaTime);

    sf::RenderWindow window_;

    Camera camera_;
    sf::Clock clock_;
    sf::Time lastUpdate_;

    static constexpr uint32_t sceneCount = 3;
    uint32_t currentSceneIdx = 1;

    Player *player_ptr;
    EnemyManager *enemyManager;

    /*TODO:
     * Main screen scene (buttons yay!)
     * Main game UI (health, timer)
     * Game over screen (restart button, leaderboard)
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

    //! ADD MORE SCENES HERE IF NECESSARY
    void (GameManager::*updates[sceneCount])(){
        &GameManager::titleUpdate,
        &GameManager::update,
        &GameManager::overUpdate
    };

    void (GameManager::*renders[sceneCount])(){
        &GameManager::titleRender,
        &GameManager::render,
        &GameManager::overRender
    };

    void handlePause();

};


#endif //GAME_MANAGER_H
