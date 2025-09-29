#ifndef PLAYER_H
#define PLAYER_H
#include <cmath>
#include <cstdint>

#include "../AnimationPlayer.h"
#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"
#include "../core/Observer.h"

class Player final : public Observer {
public:
    explicit Player(
        Subject &gamePausedSubjectRef);

    ~Player() override;

    void render(sf::RenderWindow &rw) const;

    void update(float dts);

    [[nodiscard]] sf::Vector2f getPosition() const { return position; }

    void handleMovement(float dt, bool left, bool right);

    [[nodiscard]] sf::Angle getAngle() const { return phi; }

    void onNotify() override;

private:
    const std::string animationJsonPath = "assets/player/animation.json";
    bool gamePaused = false;

    uint8_t health = 3;
    sf::Vector2f position;
    sf::Vector2f velocity;

    sf::Vector2f collisionBoxDimensions{42.f,42.f};
    sf::IntRect textureRect;
    sf::Sprite *sprite;

    AnimationPlayer animationPlayer{};

    const float accelerationRate = 200.f;
    const float decelerationRate = 300.f;
    const float maxSpeed = 300.f;
    const double maxSpeedSquared = std::pow(maxSpeed, 2);
    const sf::Angle phi = sf::radians(M_PI / 8);
};


#endif //PLAYER_H
