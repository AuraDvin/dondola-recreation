#include "GameManager.h"

#include <cmath>
#include <iostream>


GameManager::GameManager() {
    window.setFramerateLimit(0);
    try {
        player = new Player(
            window,
            "assets/square.png",
            cameraPosition);
    } catch (const std::exception &e) {
        std::cout << "Error occured while loading player, check assets\n";
        std::cout << "Actual what:\n" << e.what() << std::endl;
        window.close();
    }

    updates[0] = &titleUpdate;
    renders[0] = &titleRender;

    updates[1] = &update;
    renders[1] = &render;

    updates[2] = &overUpdate;
    renders[2] = &overRender;

    // set first update
    lastUpdate = clock_.getElapsedTime();
    goToScene(1);
    runCurrentScene();
}

GameManager::~GameManager() {
    delete player;
}

void GameManager::update() {
    // Calculate deltaTime in seconds
    sf::Time currentTime = clock_.getElapsedTime();
    float deltaTime = (currentTime - lastUpdate).asSeconds();
    lastUpdate = currentTime;

    // Player update
    player->update(deltaTime);

    while (const std::optional<sf::Event> ev = window.pollEvent()) {
        sf::Event event = ev.value();
        if (event.is<sf::Event::Closed>())
            window.close();
    }

}



void GameManager::render() {
    window.clear(sf::Color::Black);

    // iterate over all the sprites and render them
    player->render();
    // Probably EnemyList like a linked list or even a vector or smth


    // Set the camera position
    // Techincally the same as player position, but I digress
    sf::View cameraView(
        cameraPosition,
        {(float) window.getSize().x, (float) window.getSize().y});
    window.setView(cameraView);
    window.display();
}

void GameManager::goToScene(uint32_t scene) {
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
