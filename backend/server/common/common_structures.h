#pragma once

#include <json/json.h>

#include <optional>
#include <string>


namespace common {
    struct TUser {
        uint64_t Id = 0;
        std::string Name;
        uint32_t Age = 0;
        uint32_t Sex = 0;
        uint32_t Orientation = 0;
        std::string City;
        std::string Bio;
    };

    std::optional<TUser> ExtractUserDataFromJson(const Json::Value& json);
}
