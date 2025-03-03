#ifndef PLAYER_H
#define PLAYER_H
#include <cmath>
#include <cstdint>

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"
#include "jsonReader.h"

class Player {
    uint32_t health = 3;
    sf::Vector2f position;
    sf::Vector2f playerVelocity;

    sf::IntRect rect_;
    sf::Texture texture_;
    sf::Sprite *sprite_;

    sf::RenderWindow *window;

    const float accelerationRate = 200.f;
    const float decelerationRate = 300.f;
    const float maxSpeed = 300.f;
    const double maxSpeedSquared = std::pow(maxSpeed, 2);
    const sf::Angle phi = sf::radians(M_PI / 8);

    /*TODO
     * make the sprite an actual spriteSheet and animate it!
     */
    int animationFrame = 0;
    int animationLength = 0;
    double animationTime = 0;
    nlohmann::json json;

public:
    explicit Player(sf::RenderWindow &renderWindow,
                    const std::string &texturePath);
    ~Player();

    void setJson(const std::string &jsonPath);

    void render() const;

    void update(float dt);

    sf::Vector2f getPosition() const { return position; }

    void handleMovement(float dt, bool left, bool right);

    sf::Angle getAngle() const { return phi; }
};


#endif //PLAYER_H
