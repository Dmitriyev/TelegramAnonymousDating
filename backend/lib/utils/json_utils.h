#pragma once

#include <json/json.h>

#include <string>

namespace utils {
    std::string GetStringValueFromJson(const Json::Value& config, const std::string& key);
    uint32_t GetUIValueFromJson(const Json::Value& config, const std::string& key);
}
