#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "Enemy.h"
#include "LinkedList.h"


class EnemyManager {
    float spawnPeriod = 2.f;
    float accumulatedTime = 0.f;
    LinkedList<Enemy> *list;

public:
    EnemyManager();

    ~EnemyManager();

    void update(float dt);

    void render(sf::RenderWindow &window);
};


#endif //ENEMYMANAGER_H
