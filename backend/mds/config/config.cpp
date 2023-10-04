#include "config.h"
#include "utils/json_utils.h"

#include <json/json.h>

#include <trantor/utils/Logger.h>
    
#include <fstream>


namespace config {
    using namespace utils;

    std::optional<TConfig> ParseConfig(const std::filesystem::path& configPath) {
        std::ifstream fileStream;
        fileStream.open(configPath.c_str());

        Json::Value configJson;
        Json::CharReaderBuilder builder;
        builder["collectComments"] = true; // Supports json file comments
        JSONCPP_STRING errors;

        if (!parseFromStream(builder, fileStream, &configJson, &errors)) {
            LOG_ERROR << "Canot parse config file " << configPath.string();
            return std::nullopt;
        }

        try {
            TConfig config {
                .ServerHost = GetStringValueFromJson(configJson, "server_host"),
                .ServerPort = GetUIValueFromJson(configJson, "server_port"),
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
