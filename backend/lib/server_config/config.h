#pragma once

#include <json/json.h>

#include <optional>


namespace server_config {
    struct TServerConfig {
        std::string Host;
        uint32_t Port = 0;
    };

    std::optional<TServerConfig> ExtractServerConfigFromJson(const Json::Value& configJson);
}
    
