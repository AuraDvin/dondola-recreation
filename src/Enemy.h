#ifndef ENEMY_H
#define ENEMY_H
#include "Player.h"
#include "SFML/Graphics.hpp"


class Enemy {
    sf::Sprite *sprite_;
    sf::Texture texture_;
    sf::IntRect rect_;

    sf::Vector2f direction;
    sf::Vector2f velocity;

    static Player *player; // player reference
    static sf::RenderWindow *render_window_; // render window reference

    const float accelerationRate = 200.f;
    const float maxSpeed = 300.f;
    const double maxSpeedSquared = std::pow(maxSpeed, 2);

    // define illegal spawns
    const float illegalSpawnX[2]{-100.f, 100.f};
    const float illegalSpawnY[2]{-100.f, 100.f};

    void setSpawn();

public:
    static void init(Player &pylr, sf::RenderWindow &rw);

    // ReSharper disable once CppDFAConstantConditions
    static bool isInitialized() { return player == nullptr || render_window_ == nullptr; }

    Enemy(const Enemy &copy);

    Enemy(const std::string &spritePath);

    sf::Vector2f getPosition() const { return sprite_->getPosition(); }

    void update(float dt);
};

Player *Enemy::player = nullptr;
sf::RenderWindow *Enemy::render_window_ = nullptr;

#endif //ENEMY_H
