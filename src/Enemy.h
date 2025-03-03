#ifndef ENEMY_H
#define ENEMY_H
#include "Player.h"
#include "SFML/Graphics.hpp"
#include "MyDebugger.h"

class Enemy {
    uint32_t id = 0;

    sf::Sprite *sprite_;
    sf::Texture texture_;
    sf::IntRect rect_;

    sf::Vector2f direction;
    sf::Vector2f velocity;

    static Player *player_ptr; // player reference
    static sf::RenderWindow *render_window_; // render window reference

    bool outOfBounds = false;
    const double maxDist = std::pow(800.f , 2);

    const float accelerationRate = 200.f;
    const float maxSpeed = 300.f;
    const double maxSpeedSquared = std::pow(maxSpeed, 2);

    const float spawnRadius = 200.f;
    const double spawnRadiusSquared = std::pow(spawnRadius, 2);

    void setSpawn();

    void checkInBounds();


// ReSharper disable once CppDFAConstantConditions
public:
    static void init(Player *player_ref_ptr, sf::RenderWindow &rw);
    static bool isUninitialized() { return player_ptr == nullptr || render_window_ == nullptr; }

    bool operator==(const Enemy &other) const { return id == other.id; }
    bool operator!=(const Enemy &other) const { return !operator==(other); }

    Enemy(uint32_t id, const Enemy &copy);
    Enemy(uint32_t id, const std::string &spritePath);
    ~Enemy(){ debugger::print_debug("enemy id ", id, " out of bounds or collided"); }

    uint32_t getID() const { return id; }

    sf::Vector2f getPosition() const { return sprite_->getPosition(); }

    void update(float dt);

    void render(sf::RenderWindow *window) const { window->draw(*sprite_); }

    bool isOutOfBounds() const { return outOfBounds; }
};


#endif //ENEMY_H
