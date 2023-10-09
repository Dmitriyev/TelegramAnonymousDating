#include "config.h"
#include "utils/json_utils.h"

#include <trantor/utils/Logger.h>


namespace config {
    using namespace utils;

    std::optional<TConfig> ParseConfig(const Json::Value& configJson) {
        try {
            TConfig config {
                .CloudRegion = GetStringValueFromJson(configJson, "cloud_region"),
                .CloudEndpoint = GetStringValueFromJson(configJson, "cloud_endpoint"),
                .CloudKeyId = GetStringValueFromJson(configJson, "cloud_key_id"),
                .CloudKey = GetStringValueFromJson(configJson, "cloud_key"),
                .CloudBucket = GetStringValueFromJson(configJson, "cloud_bucket"),
            };

            return config;
        } catch (const std::exception& e) {
            LOG_ERROR << e.what();
            return std::nullopt;
        }
    }
}
