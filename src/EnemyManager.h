#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <unordered_set>

#include "Enemy.h"
#include "LinkedList.h"

class EnemyManager {
public:
    EnemyManager();

    ~EnemyManager();

    void update(float dt);

    void render(sf::RenderWindow &window);

    void spawnEnemy();

    uint32_t getID();
private:
    float spawnPeriodSeconds = 2.f;
    float accumulatedTime = 0.f;
    std::unordered_set<uint32_t> notAllowedIds;
    LinkedList<Enemy> enemyList;
    Enemy *baseEnemy;
};


#endif //ENEMY_MANAGER_H
