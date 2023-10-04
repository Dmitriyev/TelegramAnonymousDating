#pragma once

#include <filesystem>
#include <optional>
#include <string>

namespace config {
    struct TConfig {
        std::string ServerHost;
        uint32_t ServerPort = 0;

        std::string CloudRegion;
        std::string CloudEndpoint;
        std::string CloudKeyId;
        std::string CloudKey;
        std::string CloudBucket;
    };

    std::optional<TConfig> ParseConfig(const std::filesystem::path& configPath);
}
