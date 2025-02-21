#include "Enemy.h"
#include "prg.h"

void Enemy::setSpawn() {
    std::uniform_real_distribution<> randomAngle(0.0, 2.0 * M_PI);
    std::uniform_real_distribution<> randomDistance(400.0, 600.0);

    double phi = 0.0;
    do {
        phi = static_cast<float>(randomAngle(gen));
    //! Prevent unavoidable hits
    } while (
        sf::radians(phi) == player_ptr->getAngle() ||
        sf::radians(phi) == sf::radians(2 * M_PI) - player_ptr->getAngle()
        );
    const auto dist = static_cast<float>(randomDistance(gen));
    const auto spawnVector  = sf::Vector2f(1, 0) * dist;
    const auto playerPos = player_ptr->getPosition();
    sprite_->setPosition(playerPos + spawnVector.rotatedBy(sf::radians(phi)));
    direction = playerPos - sprite_->getPosition();
}

void Enemy::checkInBounds() {
    outOfBounds = (player_ptr->getPosition() - sprite_->getPosition()).lengthSquared() >= maxDist;
}

void Enemy::init(Player *player_ref_ptr, sf::RenderWindow &rw) {
    debugger::print_debug("initializing player and window static pointers");
    player_ptr = player_ref_ptr;
    render_window_ = &rw;
    if (isUninitialized()) throw std::runtime_error("static fields uninitialized");
}


Enemy::Enemy(const uint32_t id, const Enemy &copy) {
    if (isUninitialized()) throw std::runtime_error("static fields uninitialized");
    this->id = id;
    this->sprite_ = new sf::Sprite(*copy.sprite_);
    this->texture_ = copy.texture_;
    this->rect_ = copy.rect_;
    this->sprite_->setOrigin({this->rect_.size.x / 2.f, this->rect_.size.y / 2.f});
    setSpawn();
}

// Technically the origin should be set from baseEnemy but rather safe than sorry
Enemy::Enemy(const uint32_t id, const std::string &spritePath) {
    if (isUninitialized()) throw std::runtime_error("static fields uninitialized");
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