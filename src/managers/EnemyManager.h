#ifndef ENEMY_MANAGER_H
#define ENEMY_MANAGER_H

#include <unordered_set>

#include "../entities/Enemy.h"
#include "../core/LinkedList.h"

class EnemyManager final : public Observer {
public:
    explicit EnemyManager(Subject &gamePausedSubjectRef);

    ~EnemyManager() override;

    void update(float dt);

    void render(sf::RenderWindow &window);

    void spawnEnemy();

    uint32_t getID();

private:
    bool gamePaused = false;
    float spawnPeriodSeconds = 2.f;
    float accumulatedTime = 0.f;

    void onNotify() override;

    std::unordered_set<uint32_t> notAllowedIds;
    LinkedList<Enemy> enemyList;
    Enemy *baseEnemy;
};


#endif //ENEMY_MANAGER_H
