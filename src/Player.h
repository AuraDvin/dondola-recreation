#ifndef PLAYER_H
#define PLAYER_H
#include <cstdint>

#include "SFML/Graphics.hpp"
#include "SFML/System/Vector2.hpp"


class Player {
    uint32_t health = 3;
    sf::Vector2f position;
    sf::Vector2f playerVelocity;

    sf::IntRect *rect_;
    sf::Texture *texture_;
    sf::Sprite *sprite_;

    sf::RenderWindow *window;
    sf::Vector2f *cameraPos;

public:
    explicit Player(sf::RenderWindow &window,
                    const std::string &texturePath,
                    sf::Vector2f &cameraPosition);

    void render() const;

    void update(float dt);
};


#endif //PLAYER_H
