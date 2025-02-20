#include "Enemy.h"
#include <iostream>
#include <random>

void Enemy::setSpawn() {
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> randomAngle(0.0, 2.0 * M_PI);
    std::uniform_real_distribution<> randomDistance(200.0, 400.0);


    const auto phi = static_cast<float>(randomAngle(gen));
    const auto dist = static_cast<float>(randomDistance(gen));
    const auto spawnVector  = sf::Vector2f(1, 0) * dist;

    sprite_->setPosition(spawnVector.rotatedBy(sf::radians(phi)));
    direction = player_ptr->getPosition() - sprite_->getPosition();
}

void Enemy::checkInBounds() {
    outOfBounds = (player_ptr->getPosition() - sprite_->getPosition()).lengthSquared() >= maxDist;
}

void Enemy::init(Player *pylr, sf::RenderWindow &rw) {
    std::cout << "initializing player and window static pointers\n";
    player_ptr = pylr;
    render_window_ = &rw;
    if (isUninitialized()) throw std::runtime_error("static fields uninitialized");
}


Enemy::Enemy(uint32_t id, const Enemy &copy) {
    if (isUninitialized()) throw std::runtime_error("static fields uninitalized");
    this->id = id;
    this->sprite_ = new sf::Sprite(*copy.sprite_);
    this->texture_ = copy.texture_;
    this->rect_ = copy.rect_;
    this->sprite_->setOrigin({this->rect_.size.x / 2.f, this->rect_.size.y / 2.f});
    setSpawn();
}


Enemy::Enemy(uint32_t id, const std::string &spritePath) {
    if (isUninitialized()) throw std::runtime_error("static fields uninitalized");
    this->id = id;
    this->texture_ = sf::Texture(spritePath, false);
    this->rect_ = sf::IntRect({0, 0}, {42, 42});
    this->sprite_ = new sf::Sprite(this->texture_, this->rect_);
    this->sprite_->setOrigin({this->rect_.size.x / 2.f, this->rect_.size.y / 2.f});
    setSpawn();
}


void Enemy::update(const float dt) {
    velocity += direction.normalized() * accelerationRate;

    if (velocity.lengthSquared() > maxSpeedSquared) {
        velocity = velocity.normalized() * maxSpeed;
    }

    sprite_->setPosition(sprite_->getPosition() + velocity * dt);
    checkInBounds();
}

Player *Enemy::player_ptr = nullptr;
sf::RenderWindow *Enemy::render_window_ = nullptr;