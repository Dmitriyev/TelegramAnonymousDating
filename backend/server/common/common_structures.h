#pragma once

#include <json/json.h>

#include <optional>
#include <string>
#include <vector>

namespace common {
    using TUserId = uint64_t;
    using TUserAvatars = std::vector<std::string>;

    // Changing fields count must cause changing of FieldsCount variable
    struct TUser {
        TUserId Id = 0;                 // 1
        std::string Name;               // 2
        uint32_t Age = 0;               // 3
        uint32_t Sex = 0;               // 4
        uint32_t Orientation = 0;       // 5
        std::string City;               // 6
        std::string Bio;                // 7
        TUserAvatars Avatars;           // 8<-------|
                                        //          |
        static const uint32_t FieldsCount = 8; // --|
    };

    std::optional<TUser> ExtractUserDataFromJson(const Json::Value& json);
    Json::Value SerializeUserDataToJson(const TUser& userData);
}
