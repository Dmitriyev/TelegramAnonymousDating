#include "config.h"
#include "utils/json_utils.h"

#include <trantor/utils/Logger.h>


namespace config {
    using namespace utils;

    std::optional<TConfig> ParseConfig(const Json::Value& configJson) {
        try {
            TConfig config {
                .PostgreSQLHost = GetStringValueFromJson(configJson, "postgresql_host"),
                .PostgreSQLPort = GetStringValueFromJson(configJson, "postgresql_port"),
                .PostgreSQLDB = GetStringValueFromJson(configJson, "postgresql_db"),
                .PostgreSQLUsersTable = GetStringValueFromJson(configJson, "postgresql_user_table"),
                .PostgreSQLUser = GetStringValueFromJson(configJson, "postgresql_user"),
                .PostgreSQLPassword = GetStringValueFromJson(configJson, "postgresql_password"),
                .RedisHost = GetStringValueFromJson(configJson, "redis_host"),
                .RedisPort = GetUIValueFromJson(configJson, "redis_port"),
                .RedisUsername = GetStringValueFromJson(configJson, "redis_username"),
                .RedisPassword = GetStringValueFromJson(configJson, "redis_password"),
            };

            return config;
        } catch (const std::exception& e) {
            LOG_ERROR << e.what();
            return std::nullopt;
        }
    }
}
