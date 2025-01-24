// ReSharper disable CppTooWideScope
#include "Player.h"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <numbers>

Player::Player(sf::RenderWindow &window,
               const std::string &texturePath) {
    this->window = &window;
    position = {0.5, 0.5};
    rect_ = new sf::IntRect({0u, 0u}, {42u, 42u});
    texture_ = new sf::Texture(texturePath, false);
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


    sf::Vector2f acceleration = {0.f, 0.f};

    // Only go left and right
    // but it's going to be an angle
    // so later the y will change too
    if (isKeyPressed(sf::Keyboard::Key::A)) {
        acceleration.x -= accelerationRate; // Accelerate left
    }
    if (isKeyPressed(sf::Keyboard::Key::D)) {
        acceleration.x += accelerationRate; // Accelerate right
    }

    // Update velocity based on acceleration
    playerVelocity += acceleration * dt;

    // Apply deceleration
    if (acceleration == sf::Vector2f(0.f, 0.f)) {
        if (playerVelocity.x > 0.f) {
            playerVelocity.x -= decelerationRate * dt;
            if (playerVelocity.x < 0.f) playerVelocity.x = 0.f;
        } else if (playerVelocity.x < 0.f) {
            playerVelocity.x += decelerationRate * dt;
            if (playerVelocity.x > 0.f) playerVelocity.x = 0.f;
        }
        if (playerVelocity.y > 0.f) {
            playerVelocity.y -= decelerationRate * dt;
            if (playerVelocity.y < 0.f) playerVelocity.y = 0.f;
        } else if (playerVelocity.y < 0.f) {
            playerVelocity.y += decelerationRate * dt;
            if (playerVelocity.y > 0.f) playerVelocity.y = 0.f;
        }
    }
    // const sf::Vector2f dir = {
    //     static_cast<float>(std::cos(M_PI * 0.75)),
    //     static_cast<float>(std::sin(M_PI * 0.75))
    // };

    // playerVelocity.x *= std::cos(M_PI * 0.75);
    // playerVelocity.y *= std::sin(M_PI * 0.75);

    // const auto val = playerVelocity.angleTo(dir);


    // Limit speed
    if (playerVelocity.lengthSquared() > maxSpeedSquared) {
        playerVelocity = playerVelocity.normalized() * maxSpeed;
    }

    sf::Vector2f rotated = playerVelocity.rotatedBy(phi);
    // playerVelocity = playerVelocity.rotatedBy(phi);
    // std::cout << "Player velocity: " << playerVelocity.x << ", " << playerVelocity.y << std::endl;
    // std::cout << "Rotated velocity: " << rotated.x << ", " << rotated.y << std::endl;

    position += rotated * dt;
}
