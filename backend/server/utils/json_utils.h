#pragma once

#include <json/json.h>

#include <algorithm>
#include <string>

namespace utils {
    std::string GetStringValueFromJson(const Json::Value& config, const std::string& key);
    uint32_t GetUIValueFromJson(const Json::Value& config, const std::string& key);
    std::vector<uint32_t> GetUIListFromJson(const Json::Value& config, const std::string& key);

    template <class T>
    Json::Value ToJson(const std::vector<T>& vec) {
        Json::Value value(Json::arrayValue);
        std::for_each(vec.begin(), vec.end(), [&value](const T& vecValue) {
            value.append(vecValue);
        });
        return value;
    }
}
