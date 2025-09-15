#include "Player.h"
#include "../TextureLoader.h"

Player::Player(sf::RenderWindow &renderWindow,
               const std::string &texturePath,
               Subject &gamePausedSubjectRef) : Observer(gamePausedSubjectRef){
    position = {0.5, 0.5};
    texture_ = sf::Texture(texturePath, false);
    rect_ = sf::IntRect({0u, 0u}, {42u, 42u});
    sprite_ = new sf::Sprite(texture_, rect_);
    sprite_->setOrigin(sf::Vector2f(rect_.size) / 2.f);
    animationPlayer_ = AnimationPlayer(this->animationJsonPath);
    animationPlayer_.playAnimation("idle");
}

Player::~Player() {
    delete sprite_;
    Observer::~Observer();
}


void Player::render(sf::RenderWindow& rw) const {
    sprite_->setPosition(position);
    sprite_->setTextureRect(rect_);
    sprite_->setScale(sf::Vector2f(42.f/rect_.size.x, 42.f/rect_.size.y));
    rw.draw(*this->sprite_);
}

void Player::update(const float dts) {
    if (gamePaused) return;

    rect_ = animationPlayer_.updateAnimation(dts);

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

    const sf::Vector2f rotated = playerVelocity.rotatedBy(phi);

    position += rotated * dt;
}


void Player::onNotify() {
    gamePaused = !gamePaused;
}