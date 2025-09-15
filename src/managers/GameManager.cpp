#include "GameManager.h"

#include <cmath>
#include <random>

#include "../TextureLoader.h"
#include "../GamePaused.h"

constexpr int UNLIMITED_FRAMERATE = 0;

void GameManager::updateCamera(const float deltaTime) {
    // ReSharper disable once CppTooWideScopeInitStatement
    const float distSquared = (camera_.position - player_ptr->getPosition()).lengthSquared();
    if (distSquared > camera_.maxPlayerDistanceSquared) {
        const sf::Vector2f dir = (player_ptr->getPosition() - camera_.position).normalized();
        camera_.velocity += dir * (deltaTime * camera_.accelerationRate);
    }
    // else if (100.f < distSquared < camera_.minPlayerDistanceSquared) {
    //     camera_.velocity = {0.f, 0.f};
    //     camera_.position = player->getPosition();
    // }
    else {
        if (camera_.velocity.x > 0.f) {
            camera_.velocity.x -= camera_.decelerationRate * deltaTime;
            camera_.velocity.x = std::max(camera_.velocity.x, 0.f);
        } else {
            camera_.velocity.x += camera_.decelerationRate * deltaTime;
            camera_.velocity.x = std::min(camera_.velocity.x, 0.f);
        }
        if (camera_.velocity.y > 0.f) {
            camera_.velocity.y -= camera_.decelerationRate * deltaTime;
            camera_.velocity.y = std::max(camera_.velocity.y, 0.f);
        } else {
            camera_.velocity.y += camera_.decelerationRate * deltaTime;
            camera_.velocity.y = std::min(camera_.velocity.y, 0.f);
        }
    }

    if (camera_.velocity.lengthSquared() > camera_.maxSpeedSquared) {
        camera_.velocity = camera_.velocity.normalized() * camera_.maxSpeed;
    }

    camera_.position += camera_.velocity * deltaTime;
}

GameManager::GameManager() : window_(sf::VideoMode({1280u, 720u}), gameName) {
    // TODO: make and load spritesheet
    // loadSpriteSheet();
    window_.setFramerateLimit(UNLIMITED_FRAMERATE);
    try {
        player_ptr = new Player(
            window_,
            "assets/square.png",
            gamePausedSubject);

    } catch (const std::exception &e) {
        // Always debug on exception
        debugger::debug_mode = true;
        debugger::print_debug(
            "Error occurred while loading player, check assets\n",
            "Actual what: ", e.what()
        );
        window_.close();
        exit(EXIT_FAILURE);
    }

    Enemy::init(player_ptr, window_);
    enemyManager = new EnemyManager(gamePausedSubject);

    // set first update
    lastUpdate_ = clock_.getElapsedTime();
    goToScene(1); //
    runCurrentScene();
}

GameManager::~GameManager() {
    debugger::print_debug("GameManager::~GameManager()",
                          " deleting enemy list and player");
    delete enemyManager;
    delete player_ptr;
}

void GameManager::update() {
    // Calculate deltaTime in seconds
    const sf::Time currentTime = clock_.getElapsedTime();
    const float deltaTimeSeconds = (currentTime - lastUpdate_).asSeconds();
    lastUpdate_ = currentTime;

    handlePause();

    // Player update
    player_ptr->update(deltaTimeSeconds);

    // TODO: lerp camera to player
    // current behavior is a bit "swing-y" but its alright for now
    // updateCamera(deltaTime);

    // Update enemies
    enemyManager->update(deltaTimeSeconds);

    while (const std::optional<sf::Event> ev = window_.pollEvent()) {
        if (sf::Event event = ev.value(); event.is<sf::Event::Closed>())
            window_.close();
        if (isKeyPressed(sf::Keyboard::Key::L)) {
            debugger::print_debug("rocket spawn (keyboard event)");
            enemyManager->spawnEnemy();
        }
    }
}


void GameManager::render() {
    window_.clear(sf::Color::Black);

    //TODO: Render background
    player_ptr->render(window_);
    enemyManager->render(window_);

    // Set the camera position
    // Technically the same as player position, but I digress
    const sf::View cameraView(
        camera_.position,
        {
            static_cast<float>(window_.getSize().x),
            static_cast<float>(window_.getSize().y)
        });
    window_.setView(cameraView);
    window_.display();
}

void GameManager::titleUpdate() {
}

void GameManager::titleRender() {
}

void GameManager::overUpdate() {
}

void GameManager::overRender() {
}

void GameManager::handlePause() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
        if (!pausePressedOnLastUpdate) {
            pausePressedOnLastUpdate = true;
            // gamePausedSubject.send();
        }
    } else if (pausePressedOnLastUpdate) {
        pausePressedOnLastUpdate = false;
        /// Only sending on letting go of pause
        gamePausedSubject.send();
    }
}

void GameManager::goToScene(const uint32_t sceneIdx) {
    if (sceneIdx >= sceneCount) {
        window_.close();
        throw std::runtime_error("Requested index of scene: "
                                 + std::to_string(sceneIdx)
                                 + " is ouf of bounds (max: "
                                 + std::to_string(sceneCount)
                                 + ") Remember to use uint32_t!");
    }
    this->currentSceneIdx = sceneIdx;
}

void GameManager::runCurrentScene() {
    while (window_.isOpen()) {
        (this->*updates[currentSceneIdx])();
        (this->*renders[currentSceneIdx])();
    }
}
