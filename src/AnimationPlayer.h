#ifndef DONDOLAGAME_RECREATION_ANIMATIONPLAYER_H
#define DONDOLAGAME_RECREATION_ANIMATIONPLAYER_H
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <cstdint>

#include "SFML/Graphics/Rect.hpp"

struct Frame {
    float duration;
    sf::IntRect rect;

    Frame(const float duration, const sf::IntRect rect) : duration(duration), rect(rect) {
    }

    Frame() : duration(0) {
    };
};

constexpr int FIRST_FRAME = 0;

struct Animation {
    int frameCount;
    bool looping;
    std::string nextAnimation;
    std::vector<Frame> frames = std::vector<Frame>();

    Animation(const int frameCount, const bool looping, std::string nextAnimation) : frameCount(frameCount),
        looping(looping), nextAnimation(std::move(nextAnimation)) {
    }

    Animation() : frameCount(0), looping(false) {
    }

    ~Animation() = default;
};

class AnimationPlayer final {
public:
    AnimationPlayer() = default;

    ~AnimationPlayer() = default;
    /// <summary>
    /// Attempts to make a map of animations with:
    /// 'Animation Name' : 'Frames'
    ///  structure
    /// </summary>
    /// @param jsonAnimationPath path to the json file with correct animation structure
    explicit AnimationPlayer(const std::string &jsonAnimationPath);

    /// Tries to get the animation from the map and set it as the current playing animation
    void playAnimation(const std::string &animationName);

    /// Changes frame index and loops/changes animation based on time passed
    /// Updates a local sinceLastTime variable with deltaTime. If deltaTime is very large
    /// it will at most update to the next (1) frame per function call!
    /// @return returns the rect of the next frame to set for sprite to use
    sf::Rect<int> updateAnimation(double deltaTimeSeconds);

private:
    uint32_t currentFrameIndex = 0;
    double sinceLastFrameSeconds = 0.0;
    std::string currentAnimationName;
    Animation currentAnimation;
    std::map<std::string, Animation> animations;
};


#endif //DONDOLAGAME_RECREATION_ANIMATIONPLAYER_H
