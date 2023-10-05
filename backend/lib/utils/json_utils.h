#pragma once

#include <json/json.h>

#include <string>
#include <vector>


namespace utils {
    // All methods throws exceptions
    // Helpers exists because jsoncpp contributors write shitcode that aborts program when throwing exception needed
    // https://github.com/open-source-parsers/jsoncpp/blob/master/include/json/assertions.h#L49
    // ToDo: Use other json library

    std::string GetStringValueFromJson(const Json::Value& value, const std::string& key);
    uint32_t GetUIValueFromJson(const Json::Value& value, const std::string& key);
    std::vector<std::string> GetStringVectorFromJson(const Json::Value& value, const std::string& key);
}
