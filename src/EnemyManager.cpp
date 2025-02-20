#include "EnemyManager.h"


EnemyManager::EnemyManager(sf::RenderWindow &rw, Player *plyr) {
    list = new LinkedList<Enemy>;
    // Enemy::init(plyr, rw);
    std::cout << "Static fields set!\n";
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

    for (Node<Enemy> *i = list->getStart(); i != nullptr;) {
        if (i->val.isOutOfBounds()) {
            // id is now legal
            notAllowedIds.erase(i->val.getID());
            Node<Enemy> *tmp = i->next;
            list->remove(i->val);
            i = tmp;
            continue;
        }
        i = i->next;
    }

    // iterate and update all enemies
    list->update(dt);
}

void EnemyManager::render(sf::RenderWindow &window) {
    // iterate and draw all enemies
    list->render(window);
}

void EnemyManager::spawnEnemy() {
    // make enemy object and give it the id
    uint32_t id = getID();
    list->add(Enemy(id, *baseEnemy));
}

uint32_t EnemyManager::getID() {
    uint32_t id = rand();
    while (notAllowedIds.find(id) != notAllowedIds.end()) {
        id = rand();
    }
    notAllowedIds.insert(id);
    return id;
}
