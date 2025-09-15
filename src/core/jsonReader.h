//
// Created by aura on 22/02/25.
//

#ifndef JSONREADER_H
#define JSONREADER_H
#include <nlohmann/json.hpp>
#include <fstream>

class jsonReader {
    public:
    nlohmann::json json;
    explicit jsonReader(const std::string &jsonPath);
};



#endif //JSONREADER_H
