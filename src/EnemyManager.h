#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <unordered_set>

#include "Enemy.h"
#include "LinkedList.h"


class EnemyManager {
    float spawnPeriod = 2.f;
    float accumulatedTime = 0.f;
    std::unordered_set<uint32_t> notAllowedIds;
    LinkedList<Enemy> *list;
    Enemy *baseEnemy;

public:
    EnemyManager(sf::RenderWindow &rw, Player &plyr);

    ~EnemyManager();

    void update(float dt);

    void render(sf::RenderWindow &window);

    void spawnEnemy();

    uint32_t getID();
};


#endif //ENEMYMANAGER_H
