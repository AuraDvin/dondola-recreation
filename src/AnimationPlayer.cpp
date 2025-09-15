#include "AnimationPlayer.h"

#include "core/jsonReader.h"

AnimationPlayer::AnimationPlayer(const std::string &jsonAnimationPath) {
    jsonReader reader(jsonAnimationPath);
    for (auto json = reader.json.begin(); json != reader.json.end(); ++json) {
        std::string name = json.key();
        std::string nextAnimName;
        int frameCount;
        bool looping;

        json.value().at("frameCount").get_to(frameCount);
        json.value().at("looping").get_to(looping);
        json.value().at("nextAnimation").get_to(nextAnimName);

        Animation animation(frameCount, looping, nextAnimName);


        for (auto frame: json.value().at("frames")) {
            float duration;
            int x, y, width, height;
            frame.at("duration").get_to(duration);
            frame.at("rect").get_to(x);
            frame.at("rect").get_to(y);
            frame.at("rect").get_to(width);
            frame.at("rect").get_to(height);
            auto position = sf::Vector2i(x, y);
            auto size = sf::Vector2i(width, height);
            // Implicit makes a Frame object
            animation.frames.emplace_back(duration, sf::IntRect(position, size));
        }

        animations.emplace(name, animation);

        // set a default value - first value in json
        if (currentAnimationName.empty()) {
            currentAnimationName = name;
        }
    }
    currentAnimation = animations.at(currentAnimationName);
}

void AnimationPlayer::playAnimation(const std::string &animationName) {
    if (animationName == currentAnimationName) {
        return; // continue current animation
    }
    currentFrameIndex = 0;
    currentAnimationName = animationName;
    currentAnimation = animations.at(animationName);
}

void AnimationPlayer::updateAnimation(const double deltaTime) {
    sinceLastFrame += deltaTime;
    if (currentFrameIndex < FIRST_FRAME) {
        currentFrameIndex = FIRST_FRAME; // do not go out of bounds, just in case
    }
    const float currentFrameDuration = currentAnimation.frames[currentFrameIndex].duration;
    if (sinceLastFrame < currentFrameDuration) {
        return;
    }
    sinceLastFrame = std::max(sinceLastFrame - currentFrameDuration, 0.0);
    currentFrameIndex++;
    if (currentFrameIndex < currentAnimation.frameCount) {
        return;
    }
    currentFrameIndex = FIRST_FRAME;
    if (!currentAnimation.looping) {
        currentAnimationName = currentAnimation.nextAnimation;
        currentAnimation = animations.at(currentAnimationName);
    }
}
