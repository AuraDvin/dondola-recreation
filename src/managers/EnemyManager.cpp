#include "EnemyManager.h"
#include "../core/prg.h"
#include "../core/Subject.h"


EnemyManager::EnemyManager(Subject &gamePausedSubjectRef) : Observer(gamePausedSubjectRef),
                                                            enemyList(LinkedList<Enemy>()),
                                                            baseEnemy(new Enemy(0)) {
}

EnemyManager::~EnemyManager() {
    delete baseEnemy;
}

void EnemyManager::update(const float dt) {
    if (gamePaused) return;

    for (accumulatedTime += dt; accumulatedTime >= spawnPeriodSeconds; accumulatedTime -= spawnPeriodSeconds) {
        spawnEnemy();
    }

    for (Node<Enemy> *enemyNode = enemyList.getStart(); enemyNode != nullptr; enemyNode = enemyNode->next) {
        enemyNode->val.update(dt);
        if (enemyNode->val.checkOutOfBounds()) {
            notAllowedIds.erase(enemyNode->val.getID());
            enemyNode = enemyList.remove(enemyNode->val);
        }
    }
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

void EnemyManager::onNotify() {
    gamePaused ^= true;
}
