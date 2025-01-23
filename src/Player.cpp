// ReSharper disable CppTooWideScope
#include "Player.h"

#include <cmath>

Player::Player(sf::RenderWindow &window,
               const std::string &texturePath,
               sf::Vector2f &cameraPosition) {
    this->window = &window;
    position = {0.5, 0.5};
    rect_ = new sf::IntRect({0u, 0u}, {42u, 42u});
    texture_ = new sf::Texture(texturePath, false);
    cameraPos = &cameraPosition;
    sprite_ = new sf::Sprite(*texture_, *rect_);
    sprite_->setOrigin(sf::Vector2f(rect_->size) / 2.f);
}

void Player::render() const {
    sprite_->setPosition(position);
    window->draw(*sprite_);
}

void Player::update(float dt) {
    // maxSpeedSquare is used for comparrison,
    // apparently it's faseter
    constexpr float accelerationRate = 200.f;
    constexpr float decelerationRate = 300.f;
    constexpr float maxSpeed = 300.f;
    constexpr double maxSpeedSquared = std::pow(maxSpeed, 2);

    sf::Vector2f acceleration = {0.f, 0.f};

    // Only go left and right
    // but it's going to be an angle
    // so later the y will change too
    if (isKeyPressed(sf::Keyboard::Key::A)) {
        acceleration.x -= accelerationRate;  // Accelerate left
    }
    if (isKeyPressed(sf::Keyboard::Key::D)) {
        acceleration.x += accelerationRate;  // Accelerate right
    }

    // Update velocity based on acceleration
    playerVelocity += acceleration * dt;

    // Apply deceleration
    if (acceleration == sf::Vector2f(0.f, 0.f)) {
        if (playerVelocity.x > 0.f) {
            playerVelocity.x -= decelerationRate * dt;
            if (playerVelocity.x < 0.f) playerVelocity.x = 0.f;
        }
        else if (playerVelocity.x < 0.f) {
            playerVelocity.x += decelerationRate * dt;
            if (playerVelocity.x > 0.f) playerVelocity.x = 0.f;
        }
        if (playerVelocity.y > 0.f) {
            playerVelocity.y -= decelerationRate * dt;
            if (playerVelocity.y < 0.f) playerVelocity.y = 0.f;
        }
        else if (playerVelocity.y < 0.f) {
            playerVelocity.y += decelerationRate * dt;
            if (playerVelocity.y > 0.f) playerVelocity.y = 0.f;
        }
    }

    // Limit speed
    if (playerVelocity.lengthSquared() > maxSpeedSquared) {
        playerVelocity = playerVelocity.normalized() * maxSpeed;
    }

    position += playerVelocity * dt;
}
