#include "GameManager.h"

#include <cmath>
#include <iostream>
#include <random>

void GameManager::updateCamera(const float deltaTime) {
    // ReSharper disable once CppTooWideScopeInitStatement
    const float distSquared = (camera_.position - player->getPosition()).lengthSquared();
    if (distSquared > camera_.maxPlayerDistanceSquared) {
        const sf::Vector2f dir = (player->getPosition() - camera_.position).normalized();
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

GameManager::GameManager() {
    window.setFramerateLimit(0);
    try {
        player = new Player(
            window,
            "assets/square.png");
    } catch (const std::exception &e) {
        // Always debug on exception
        debugger::debug_mode = true;
        debugger::print_debug(
            "Error occurred while loading player, check assets\n",
            "Actual what: ", e.what()
        );
        window.close();
        exit(EXIT_FAILURE);
    }

    Enemy::init(player, window);
    em = new EnemyManager();

    // set first update
    lastUpdate = clock_.getElapsedTime();
    goToScene(1); //
    runCurrentScene();
}

GameManager::~GameManager() {
    debugger::print_debug("GameManager::~GameManager()",
        " deleting enemy list and player");
    delete em;
    delete player;
}

void GameManager::update() {
    // Calculate deltaTime in seconds
    const sf::Time currentTime = clock_.getElapsedTime();
    const float deltaTime = (currentTime - lastUpdate).asSeconds();
    lastUpdate = currentTime;

    // Player update
    player->update(deltaTime);

    // TODO: lerp camera to player
    // current behavior is a bit "swing-y" but its alright for now
    // updateCamera(deltaTime);

    // Update enemies
    em->update(deltaTime);

    while (const std::optional<sf::Event> ev = window.pollEvent()) {
        if (sf::Event event = ev.value(); event.is<sf::Event::Closed>())
            window.close();
        if (isKeyPressed(sf::Keyboard::Key::L)) {
            debugger::print_debug("rocket spawn (keyboard event)");
            em->spawnEnemy();
        }
    }
}


void GameManager::render() {
    window.clear(sf::Color::Black);

    //TODO: Render background
    player->render();
    em->render(window);

    // Set the camera position
    // Technically the same as player position, but I digress
    const sf::View cameraView(
        camera_.position,
        {
            static_cast<float>(window.getSize().x),
            static_cast<float>(window.getSize().y)
        });
    window.setView(cameraView);
    window.display();
}

void GameManager::titleUpdate() {
}

void GameManager::titleRender() {
}

void GameManager::overUpdate() {
}

void GameManager::overRender() {
}

void GameManager::goToScene(const uint32_t scene) {
    if (scene >= sceneCount) {
        window.close();
        throw std::runtime_error("Requested index of scene: "
                                 + std::to_string(scene)
                                 + " is ouf of bounds (max: "
                                 + std::to_string(sceneCount)
                                 + ") Remember to use uint32_t!");
    }
    this->curScene = scene;
}

void GameManager::runCurrentScene() {
    while (window.isOpen()) {
        (this->*updates[curScene])();
        (this->*renders[curScene])();
    }
}
