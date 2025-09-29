#include "Player.h"
#include "../TextureLoader.h"

Player::Player(
    Subject &gamePausedSubjectRef) : Observer(gamePausedSubjectRef) {
    position = {0.5, 0.5};
    textureRect = sf::IntRect({0u, 0u}, {42u, 42u});
    sprite = new sf::Sprite(*Texture::spriteSheet, textureRect);
    sprite->setOrigin(sf::Vector2f(textureRect.size) / 2.f);
    animationPlayer = AnimationPlayer(this->animationJsonPath);
    animationPlayer.playAnimation("idle");
}

Player::~Player() {
    delete sprite;
    Observer::~Observer();
}


void Player::render(sf::RenderWindow &rw) const {
    sprite->setPosition(position);
    sprite->setTextureRect(textureRect);
    sprite->setScale(sf::Vector2f(42.f / textureRect.size.x, 42.f / textureRect.size.y));
    rw.draw(*this->sprite);
}

void Player::update(const float dts) {
    if (gamePaused) return;

    textureRect = animationPlayer.updateAnimation(dts);

    const bool left = isKeyPressed(sf::Keyboard::Key::A) || isKeyPressed(sf::Keyboard::Key::Left);
    const bool right = isKeyPressed(sf::Keyboard::Key::D) || isKeyPressed(sf::Keyboard::Key::Right);

    // This wil probably require you to also update which animation it should be playing or leaving the idle one, idk
    handleMovement(dts, left, right);
}

void Player::handleMovement(const float dt, const bool left, const bool right) {
    sf::Vector2f acceleration = {0.f, 0.f};
    // Only go left and right
    // Then angle accordingly
    if (left) {
        acceleration.x -= accelerationRate;
    }
    if (right) {
        acceleration.x += accelerationRate;
    }

    // Update velocity based on acceleration
    velocity += acceleration * dt;

    // Apply deceleration if no input
    if (!(left || right)) {
        if (velocity.x > 0.f) {
            velocity.x -= decelerationRate * dt;
            if (velocity.x < 0.f) velocity.x = 0.f;
        } else if (velocity.x < 0.f) {
            velocity.x += decelerationRate * dt;
            if (velocity.x > 0.f) velocity.x = 0.f;
        }
        if (velocity.y > 0.f) {
            velocity.y -= decelerationRate * dt;
            if (velocity.y < 0.f) velocity.y = 0.f;
        } else if (velocity.y < 0.f) {
            velocity.y += decelerationRate * dt;
            if (velocity.y > 0.f) velocity.y = 0.f;
        }
    }

    // Limit speed
    if (velocity.lengthSquared() > maxSpeedSquared) {
        velocity = velocity.normalized() * maxSpeed;
    }

    const sf::Vector2f rotated = velocity.rotatedBy(phi);

    position += rotated * dt;
}


void Player::onNotify() {
    gamePaused = !gamePaused;
}
