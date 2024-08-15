#include "Utils.h"
#include <fstream>

Json::Value Utils::readConfig(const std::string& filePath) {
    std::ifstream config_file(filePath, std::ifstream::binary);
    Json::Value config;
    config_file >> config;
    return config;
}
