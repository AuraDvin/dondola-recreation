// ReSharper disable CppTooWideScope
#include "Player.h"

Player::Player(sf::RenderWindow &renderWindow,
               const std::string &texturePath) {
    window = &renderWindow;
    position = {0.5, 0.5};
    rect_ = sf::IntRect({0u, 0u}, {42u, 42u});
    texture_ = sf::Texture(texturePath, false);
    sprite_ = new sf::Sprite(texture_, rect_);
    sprite_->setOrigin(sf::Vector2f(rect_.size) / 2.f);
}

Player::~Player() {
    delete sprite_;
}

void Player::render() const {
    sprite_->setPosition(position);
    window->draw(*sprite_);
}

void Player::update(const float dt) {
    // maxSpeedSquare is used for comparison,
    // apparently it's faster

    sf::Vector2f acceleration = {0.f, 0.f};

    const bool left = isKeyPressed(sf::Keyboard::Key::A) || isKeyPressed(sf::Keyboard::Key::Left);
    const bool right = isKeyPressed(sf::Keyboard::Key::D) || isKeyPressed(sf::Keyboard::Key::Right);

    // Only go left and right
    // Then angle accordingly
    if (left) {
        acceleration.x -= accelerationRate;
    }
    if (right) {
        acceleration.x += accelerationRate;
    }

    // Update velocity based on acceleration
    playerVelocity += acceleration * dt;

    // Apply deceleration if no input
    if (!(left || right)) {
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

    // Limit speed
    if (playerVelocity.lengthSquared() > maxSpeedSquared) {
        playerVelocity = playerVelocity.normalized() * maxSpeed;
    }

    sf::Vector2f rotated = playerVelocity.rotatedBy(phi);

    position += rotated * dt;
}
