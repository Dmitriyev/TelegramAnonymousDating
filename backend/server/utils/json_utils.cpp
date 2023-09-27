#include "json_utils.h"

#include <sstream>


namespace {
    void CheckFieldExistance(const Json::Value& config, const std::string& key) {
        if (!config.isMember(key)) {
            std::stringstream errorMessage;
            errorMessage << "Config has no field named " << key;
            throw std::runtime_error(errorMessage.str());
        }
    }
}

namespace utils {
    std::string GetStringValueFromJson(const Json::Value& config, const std::string& key) {
        CheckFieldExistance(config, key);

        if (!config[key].isString()) {
            std::stringstream errorMessage;
            errorMessage << key << " field must have string type";
            throw std::runtime_error(errorMessage.str());
        }

        return config[key].asString();
    }

    uint32_t GetUIValueFromJson(const Json::Value& config, const std::string& key) {
        CheckFieldExistance(config, key);

        if (!config[key].isUInt()) {
            std::stringstream errorMessage;
            errorMessage << key << " field must have uint type";
            throw std::runtime_error(errorMessage.str());
        }

        return config[key].asUInt();

    }
}
