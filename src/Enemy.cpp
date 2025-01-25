#include "Enemy.h"


void Enemy::setSpawn() {
    srand(static_cast<unsigned>(time(NULL)));
    float x, y;
    do {
        x = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
        y = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    } while (!(x < 0.2f || x > 0.8f || y < 0.2f || y > 0.2f));

    const sf::Vector2f playerPos = player->getPosition();
    const float minX = playerPos.x + illegalSpawnX[0];
    const float maxX = playerPos.x + illegalSpawnX[1];
    const float minY = playerPos.y + illegalSpawnY[0];
    const float maxY = playerPos.y + illegalSpawnY[1];

    x = minX + x * (maxX - minX);
    y = minY + y * (maxY - minY);
    sprite_->setPosition({x, y});
    direction = playerPos - sprite_->getPosition();
}

void Enemy::checkInBounds() {
    outOfBounds = (player->getPosition() - sprite_->getPosition()).lengthSquared() >= maxDist;
}

void Enemy::init(Player &pylr, sf::RenderWindow &rw) {
    if (player == nullptr) player = &pylr;
    if (render_window_ == nullptr) render_window_ = &rw;
    if (!isInitialized()) throw std::runtime_error("static fields uninitialized");
}


Enemy::Enemy(const Enemy &copy) {
    if (!isInitialized()) throw std::runtime_error("static fields uninitalized");
    this->sprite_ = new sf::Sprite(*copy.sprite_);
    this->texture_ = copy.texture_;
    this->rect_ = copy.rect_;

    setSpawn();
}

Enemy::Enemy(const std::string &spritePath) {
    if (!isInitialized()) throw std::runtime_error("static fields uninitalized");
    this->texture_ = sf::Texture(spritePath, false);
    this->rect_ = sf::IntRect({0, 0}, {42, 42});
    this->sprite_ = new sf::Sprite(this->texture_, this->rect_);

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

Player *Enemy::player = nullptr;
sf::RenderWindow *Enemy::render_window_ = nullptr;
