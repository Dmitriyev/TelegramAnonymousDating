#pragma once

#include <json/json.h>

#include <filesystem>
#include <optional>
#include <string>
#include <vector>


namespace utils {
    std::optional<Json::Value> ParseJsonFile(const std::filesystem::path& configPath);

    // All methods below throws exceptions
    // Helpers exists because jsoncpp contributors write shitcode that aborts program when throwing exception needed
    // https://github.com/open-source-parsers/jsoncpp/blob/master/include/json/assertions.h#L49
    // ToDo: Use other json library

    std::string GetStringValueFromJson(const Json::Value& value, const std::string& key);
    uint32_t GetUIValueFromJson(const Json::Value& value, const std::string& key);
    std::vector<std::string> GetStringVectorFromJson(const Json::Value& value, const std::string& key);
}
