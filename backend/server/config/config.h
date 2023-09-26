#pragma once

#include <filesystem>
#include <optional>
#include <string>

namespace config {
    struct TConfig {
        std::string ServerHost;
        uint32_t ServerPort = 0;

        std::string PostgreSQLHost;
        std::string PostgreSQLDB;
        std::string PostgreSQLUsersTable;
        std::string PostgreSQLUser;
        std::string PostgreSQLPassword;
    };

    std::optional<TConfig> ParseConfig(const std::filesystem::path& configPath);
}
