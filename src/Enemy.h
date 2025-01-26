#ifndef ENEMY_H
#define ENEMY_H
#include "Player.h"
#include "SFML/Graphics.hpp"


class Enemy {
    uint32_t id = 0;

    sf::Sprite *sprite_;
    sf::Texture texture_;
    sf::IntRect rect_;

    sf::Vector2f direction;
    sf::Vector2f velocity;

    static Player *player; // player reference
    static sf::RenderWindow *render_window_; // render window reference

    bool outOfBounds = false;
    const double maxDist = 160'000.0;

    const float accelerationRate = 200.f;
    const float maxSpeed = 300.f;
    const double maxSpeedSquared = std::pow(maxSpeed, 2);

    // define illegal spawns
    const float illegalSpawnX[2]{-100.f, 100.f};
    const float illegalSpawnY[2]{-100.f, 100.f};

    void setSpawn();

    void checkInBounds();

public:
    static void init(Player &pylr, sf::RenderWindow &rw);

    // ReSharper disable once CppDFAConstantConditions
    static bool isInitialized() { return player == nullptr || render_window_ == nullptr; }

    bool operator==(const Enemy &other) const { return id == other.id; }
    bool operator!=(const Enemy &other) const { return !operator==(other); }

    Enemy(uint32_t id, const Enemy &copy);

    Enemy(uint32_t id, const std::string &spritePath);

    sf::Vector2f getPosition() const { return sprite_->getPosition(); }

    void update(float dt);

    void render(sf::RenderWindow *window) { window->draw(*sprite_); }

    bool isOutOfBounds() { return outOfBounds; }
};


#endif //ENEMY_H
