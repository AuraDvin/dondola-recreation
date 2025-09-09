#ifndef DONDOLAGAME_RECREATION_TEXTURE_LOADER_H
#define DONDOLAGAME_RECREATION_TEXTURE_LOADER_H

#include "MyDebugger.h"
#include "SFML/Graphics/Texture.hpp"

/// Points to the texture of every object in the game on heap
/// Has to be loaded before game can be rendered
/// Default sprite sheet path is "../assets/images/spritesheet.png" from the src directory
inline std::unique_ptr<sf::Texture> spriteSheet(new sf::Texture);
/// Default value is "../assets/images/spritesheet.png" from the src directory
inline std::string spriteSheetPath = "../assets/images/spritesheet.png";

/// Loads spritesheet specified in spriteSheetPath variable
/// Upon failure throws a runtime error
inline void loadSpriteSheet() {
    if (!spriteSheet->loadFromFile(spriteSheetPath)) {
        debugger::print_debug("Failed to load spritesheet " + spriteSheetPath);
        throw std::runtime_error("Failed to load spritesheet");
    }
    debugger::print_debug("Loaded spritesheet + " + spriteSheetPath + " successfully!");
}


#endif //DONDOLAGAME_RECREATION_TEXTURE_LOADER_H