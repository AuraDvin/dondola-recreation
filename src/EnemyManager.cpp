#include "EnemyManager.h"

#include <random>


EnemyManager::EnemyManager() {
    list = new LinkedList<Enemy>;
    baseEnemy = new Enemy(0, "assets/square.png");
}

EnemyManager::~EnemyManager() {
    delete list;
    delete baseEnemy;
}

//TODO:
// * Render
// * Update

void EnemyManager::update(const float dt) {
    for (accumulatedTime += dt; accumulatedTime >= spawnPeriod; accumulatedTime -= spawnPeriod) {
        spawnEnemy();
    }

    for (const Node<Enemy> *i = list->getStart(); i != nullptr;) {
        if (i->val.isOutOfBounds()) {
            // id is now legal
            notAllowedIds.erase(i->val.getID());
            const Node<Enemy> *tmp = i->next;
            list->remove(i->val);
            i = tmp;
            continue;
        }
        i = i->next;
    }

    // iterate and update all enemies
    list->update(dt);
}

void EnemyManager::render(sf::RenderWindow &window) const {
    // iterate and draw all enemies
    list->render(window);
}

// TODO: replace base enemy with random enemy type
void EnemyManager::spawnEnemy() {
    // make enemy object and give it the id
    const uint32_t id = getID();
    list->add(Enemy(id, *baseEnemy));
}

// Generate and return a new ID
uint32_t EnemyManager::getID() {
    std::uniform_int_distribution<uint32_t> rng(0, UINT32_MAX);
    uint32_t id;
    do {
        id = rng(gen);
    } while (notAllowedIds.find(id) != notAllowedIds.end());

    notAllowedIds.insert(id);
    return id;
}
