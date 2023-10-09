#pragma once

#include <json/json.h>

#include <optional>
#include <string>


namespace config {
    struct TConfig {
        std::string CloudRegion;
        std::string CloudEndpoint;
        std::string CloudKeyId;
        std::string CloudKey;
        std::string CloudBucket;
    };

    std::optional<TConfig> ParseConfig(const Json::Value& configJson);
}
