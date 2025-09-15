#ifndef JSONREADER_H
#define JSONREADER_H
#include <nlohmann/json.hpp>
#include <fstream>

class jsonReader {
    public:
    nlohmann::json json;
    explicit jsonReader(const std::string &jsonPath) {
        std::ifstream file(jsonPath, std::ifstream::binary);
        file >> json;
        file.close();
    }
};



#endif //JSONREADER_H
