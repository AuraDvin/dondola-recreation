//
// Created by Edvin on 23. 01. 25.
//

#include "GameManager.h"


GameManager::GameManager() {
    window.setFramerateLimit(60);
    try {
        player = new Player(window, "assets/square.png");
    } catch (const std::exception &e) {
        std::cout << "Error occured while loading player, check assets\n";
        std::cout << "Actual what:\n" << e.what() << std::endl;
        window.close();
    }

    updates[1] = &update;
    renders[1] = &render;

    // set first update
    lastUpdate = clock_.getElapsedTime();
    runCurrentScene();
}

GameManager::~GameManager() {
    delete player;
}

void GameManager::update() {
    const sf::Time time = clock_.getElapsedTime();
    int32_t delta = (time - lastUpdate).asMilliseconds();
    player->update(delta);
    lastUpdate = time;
}

void GameManager::render() {
    window.clear(sf::Color::Black);
    // iterate over all the sprites and render them
    player->render();
    // Probably EnemyList like a linked list or even a vector or smth
    window.display();
}

void GameManager::goToScene(uint32_t scene) {
    if (scene >= sceneCount)
        throw std::runtime_error("Requested index is ouf of bounds");
    this->curScene = scene;
}

void GameManager::runCurrentScene() {
    while (window.isOpen()) {
        (this->*updates[curScene])();
        (this->*renders[curScene])();
    }
}
