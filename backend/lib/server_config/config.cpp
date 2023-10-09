#include "config.h"

#include <utils/json_utils.h>


namespace server_config {
    using namespace utils;

    std::optional<TServerConfig> ExtractServerConfigFromJson(const Json::Value& configJson) {
        try {
            TServerConfig config {
                .Host = GetStringValueFromJson(configJson, "server_host"),
                .Port = GetUIValueFromJson(configJson, "server_port"),
            };

            return config;
        } catch (const std::exception& e) {
            return std::nullopt;
        }
    }
}

