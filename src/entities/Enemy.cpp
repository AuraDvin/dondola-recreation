#include "Enemy.h"

#include "../TextureLoader.h"
#include "../core/prg.h"

void Enemy::setSpawn() {
    std::uniform_real_distribution randomAngle(0.0, 2.0 * M_PI);
    std::uniform_real_distribution randomDistance(400.0, 600.0);

    float phi = 0.0;
    do {
        phi = static_cast<float>(randomAngle(gen));
        //! Prevent unavoidable hits
    } while (
        sf::radians(phi) == player_ptr->getAngle() ||
        sf::radians(phi) == sf::radians(2 * M_PI) - player_ptr->getAngle()
    );
    const auto dist = static_cast<float>(randomDistance(gen));
    const auto spawnVector = sf::Vector2f(1, 0) * dist;
    const auto playerPos = player_ptr->getPosition();
    sprite_->setPosition(playerPos + spawnVector.rotatedBy(sf::radians(phi)));
    direction = playerPos - sprite_->getPosition();
}

void Enemy::checkInBounds() {
    outOfBounds = (player_ptr->getPosition() - sprite_->getPosition()).lengthSquared() >= maxDist;
}

void Enemy::init(Player *player_ref_ptr) {
    debugger::print_debug("[Enemy] initializing player static pointers");
    player_ptr = player_ref_ptr;
    if (isUninitialized()) throw std::runtime_error("static fields uninitialized");
}


Enemy::Enemy(const uint32_t id, const Enemy &copy) : id{id},
                                                     sprite_(new sf::Sprite(*copy.sprite_)),
                                                     rect_(copy.rect_) {
    if (isUninitialized()) throw std::runtime_error("static fields uninitialized");
    this->sprite_->setOrigin({this->rect_.size.x / 2.f, this->rect_.size.y / 2.f});
    setSpawn();
}

// Technically the origin should be set from baseEnemy but rather safe than sorry
Enemy::Enemy(const uint32_t id) : id{id},
                                  rect_{{0u, 0u}, {42u, 42u}} {
    // if (isUninitialized()) throw std::runtime_error("static fields uninitialized");
    this->sprite_ = new sf::Sprite(*Texture::spriteSheet, this->rect_);
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

void Enemy::render(sf::RenderWindow &window) const {
    window.draw(*sprite_);
}

Player *Enemy::player_ptr = nullptr;
