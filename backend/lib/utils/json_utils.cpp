#include "json_utils.h"

#include <fstream>
#include <sstream>


namespace {
    void CheckFieldExistance(const Json::Value& value, const std::string& key) {
        if (!value.isMember(key)) {
            std::stringstream errorMessage;
            errorMessage << "Config has no field named " << key;
            throw std::runtime_error(errorMessage.str());
        }
    }
}

namespace utils {
    std::optional<Json::Value> ParseJsonFile(const std::filesystem::path& configPath) {
        std::ifstream fileStream;
        fileStream.open(configPath.c_str());

        Json::Value json;
        Json::CharReaderBuilder builder;
        builder["collectComments"] = true; // Supports json file comments
        JSONCPP_STRING errors;

        if (!parseFromStream(builder, fileStream, &json, &errors)) {
            return std::nullopt;
        }

        return json;
    }

    std::string GetStringValueFromJson(const Json::Value& value, const std::string& key) {
        CheckFieldExistance(value, key);

        if (!value[key].isString()) {
            std::stringstream errorMessage;
            errorMessage << key << " field must have string type";
            throw std::runtime_error(errorMessage.str());
        }

        return value[key].asString();
    }

    uint32_t GetUIValueFromJson(const Json::Value& value, const std::string& key) {
        CheckFieldExistance(value, key);

        if (!value[key].isUInt()) {
            std::stringstream errorMessage;
            errorMessage << key << " field must have uint type";
            throw std::runtime_error(errorMessage.str());
        }

        return value[key].asUInt();
    }

    std::vector<std::string> GetStringVectorFromJson(const Json::Value& value, const std::string& key) {
        CheckFieldExistance(value, key);

        if (!value[key].isArray()) {
            std::stringstream errorMessage;
            errorMessage << key << " field must have array type";
            throw std::runtime_error(errorMessage.str());
        }

        std::vector<std::string> result;
        result.reserve(value[key].size());

        for (int i = 0; i < value[key].size(); ++i) {
            if (!value[key][i].isString()) {
                throw std::runtime_error("Wrong type of array value");
            }
            result.push_back(value[key][i].asString());
        }

        return result;
    }
}
