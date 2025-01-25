#include "EnemyManager.h"


EnemyManager::EnemyManager() {
    list = new LinkedList<Enemy>;
}

EnemyManager::~EnemyManager() {
    delete list;
}
//TODO:
// * Render
// * Update

void EnemyManager::update(const float dt) {
    for (accumulatedTime += dt; accumulatedTime >= spawnPeriod; accumulatedTime -= spawnPeriod) {
        // Spawn enemy
    }
    // iterate and update all enemies
    // for (Node<Enemy> &node: list) {
    //     node.val.update(dt);
    //     if (node.val.isOutOfBounds()) {
    //
    //     }
    // }
}

void EnemyManager::render(sf::RenderWindow &window) {
    // iterate and draw all enemies
    // for (auto &node: list) {
    //     node.val.render(&window);
    // }
}
