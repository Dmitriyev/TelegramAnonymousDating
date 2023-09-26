#include "common_structures.h"
#include "utils/json_utils.h"

#include <trantor/utils/Logger.h>

#include <sstream>
#include <unordered_map>


namespace {
    enum class TNumericCodeTypes {
        Sex,
        Orientation,
    };

    using TStrToIntMap = std::unordered_map<std::string, uint32_t>;

    static const TStrToIntMap SexStrToInt {
        {"man", 0},
        {"woman", 1},
    };

    static const TStrToIntMap OrientationStrToInt {
        {"straight", 0},
        {"bi", 1},
        {"gay", 2},
    };

    static const std::unordered_map<TNumericCodeTypes, const TStrToIntMap&> StrToIntMaps {
        {TNumericCodeTypes::Sex, SexStrToInt},
        {TNumericCodeTypes::Orientation, OrientationStrToInt},
    };

    uint32_t ConvertStringToIntCode(const std::string& str, TNumericCodeTypes type) {
        const auto& mapWithCodes = StrToIntMaps.at(type);
        const auto it = mapWithCodes.find(str);
        if (it == mapWithCodes.end()) {
            std::stringstream errorMessage;
            errorMessage << "Wrong string param " << str;
            throw std::runtime_error(errorMessage.str());
        }

        return it->second;
    }
}

namespace common {
    using namespace utils;

    std::optional<TUser> ExtractUserDataFromJson(const Json::Value& json) {
        try {
            TUser user {
                .Id = GetUIValueFromJson(json, "id"),
                .Name = GetStringValueFromJson(json, "name"),
                .Age = GetUIValueFromJson(json, "age"),
                .Sex = ConvertStringToIntCode(GetStringValueFromJson(json, "sex"), TNumericCodeTypes::Sex),
                .Orientation =  ConvertStringToIntCode(GetStringValueFromJson(json, "orientation"), TNumericCodeTypes::Orientation),
                .City = GetStringValueFromJson(json, "city"),
                .Bio = GetStringValueFromJson(json, "bio"),
            };
            return user;
        } catch (const std::exception& e) {
            LOG_ERROR << e.what();
            return {};
        }
    }
}
