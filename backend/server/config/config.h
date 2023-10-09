#pragma once

#include <json/json.h>

#include <optional>
#include <string>


namespace config {
    struct TConfig {
        std::string PostgreSQLHost;
        std::string PostgreSQLPort;
        std::string PostgreSQLDB;
        std::string PostgreSQLUsersTable;
        std::string PostgreSQLUser;
        std::string PostgreSQLPassword;
    };

    std::optional<TConfig> ParseConfig(const Json::Value& configJson);
}
