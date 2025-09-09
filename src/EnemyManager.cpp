#include "EnemyManager.h"
#include "prg.h"


EnemyManager::EnemyManager() : enemyList(LinkedList<Enemy>()), baseEnemy(new Enemy(0, "assets/square.png")){
}

EnemyManager::~EnemyManager() {
    delete baseEnemy;
}

//TODO:
// * Render
// * Update

void EnemyManager::update(const float dt) {
    for (accumulatedTime += dt; accumulatedTime >= spawnPeriodSeconds; accumulatedTime -= spawnPeriodSeconds) {
        spawnEnemy();
    }

    for (const Node<Enemy> *i = enemyList.getStart(); i != nullptr;) {
        if (i->val.isOutOfBounds()) {
            // id is now legal
            notAllowedIds.erase(i->val.getID());
            const Node<Enemy> *tmp = i->next;
            enemyList.remove(i->val);
            i = tmp;
            continue;
        }
        i = i->next;
    }

    // iterate and update all enemies
    enemyList.update(dt);
}

void EnemyManager::render(sf::RenderWindow &window) {
    // iterate and draw all enemies
    enemyList.render(window);
}

// TODO: replace base enemy with random enemy type
void EnemyManager::spawnEnemy() {
    // make enemy object and give it the id
    const uint32_t id = getID();
    enemyList.add(Enemy(id, *baseEnemy));
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
