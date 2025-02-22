//
// Created by aura on 22/02/25.
//

#include "jsonReader.h"

jsonReader::jsonReader(const std::string &jsonPath) {
    std::ifstream file(jsonPath, std::ifstream::binary);
    file >> json;
    file.close();
}
