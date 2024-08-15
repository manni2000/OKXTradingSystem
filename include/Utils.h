#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <json/json.h>

class Utils {
public:
    static Json::Value readConfig(const std::string& filePath);
};

#endif
