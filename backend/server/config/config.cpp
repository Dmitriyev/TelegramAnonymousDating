#include "config.h"
#include "utils/json_utils.h"

#include <json/json.h>

#include <trantor/utils/Logger.h>
    
#include <fstream>
#include <sstream>

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
                .PostgreSQLHost = GetStringValueFromJson(configJson, "postgresql_host"),
                .PostgreSQLPort = GetStringValueFromJson(configJson, "postgresql_port"),
                .PostgreSQLDB = GetStringValueFromJson(configJson, "postgresql_db"),
                .PostgreSQLUsersTable = GetStringValueFromJson(configJson, "postgresql_user_table"),
                .PostgreSQLUser = GetStringValueFromJson(configJson, "postgresql_user"),
                .PostgreSQLPassword = GetStringValueFromJson(configJson, "postgresql_password"),
            };

            return config;
        } catch (const std::exception& e) {
            LOG_ERROR << e.what();
            return std::nullopt;
        }
    }
}
