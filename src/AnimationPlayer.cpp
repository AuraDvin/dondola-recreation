#include "AnimationPlayer.h"
#include <string>
#include "core/jsonReader.h"

AnimationPlayer::AnimationPlayer(const std::string &jsonAnimationPath) {
    jsonReader reader(jsonAnimationPath);
    try {
        for (const auto& json : reader.data.items()) {
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
                frame.at("rect").at("x").get_to(x);
                frame.at("rect").at("y").get_to(y);
                frame.at("rect").at("width").get_to(width);
                frame.at("rect").at("height").get_to(height);
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
    } catch (std::exception &e) {
        std::string test = e.what();
        test = "Error while parsing json, probably wrong format (the what):\n\t" + test;
        throw std::runtime_error(test);
    }
}

void AnimationPlayer::playAnimation(const std::string &animationName) {
    if (animationName == currentAnimationName) {
        return; // continue current animation
    }
    const auto it = animations.find(animationName);
    if (it == animations.end()) {
        throw std::invalid_argument(
            "AnimationPlayer::playAnimation: Animation: \"" + animationName + "\" does not exist!");
    }

    currentFrameIndex = FIRST_FRAME;
    currentAnimationName = animationName;
    currentAnimation = it->second;
}

void AnimationPlayer::updateAnimation(const double deltaTime) {
    sinceLastFrame += deltaTime;
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
