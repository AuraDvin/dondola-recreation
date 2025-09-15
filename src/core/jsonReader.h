#ifndef JSONREADER_H
#define JSONREADER_H
#include <nlohmann/json.hpp>
#include <fstream>

class jsonReader {
public:
    nlohmann::json data;

    explicit jsonReader(const std::string &jsonPath) {
        std::ifstream file(jsonPath);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open json file: \"" + jsonPath + "\"");
        }
        file >> data;
        file.close();
    }
};


#endif //JSONREADER_H
