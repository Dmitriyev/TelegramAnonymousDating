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

    // Json field fields 
    static const std::string IdKey = "id";
    static const std::string NameKey = "name";
    static const std::string AgeKey = "age";
    static const std::string SexKey = "sex";
    static const std::string OrientationKey = "orientation";
    static const std::string CityKey = "city";
    static const std::string BioKey = "bio";
}

namespace common {
    using namespace utils;

    std::optional<TUser> ExtractUserDataFromJson(const Json::Value& json) {
        try {
            TUser user {
                .Id = GetUIValueFromJson(json, IdKey),
                .Name = GetStringValueFromJson(json, NameKey),
                .Age = GetUIValueFromJson(json, AgeKey),
                .Sex = ConvertStringToIntCode(GetStringValueFromJson(json, SexKey), TNumericCodeTypes::Sex),
                .Orientation =  ConvertStringToIntCode(GetStringValueFromJson(json, OrientationKey), TNumericCodeTypes::Orientation),
                .City = GetStringValueFromJson(json, CityKey),
                .Bio = GetStringValueFromJson(json, BioKey),
            };
            return user;
        } catch (const std::exception& e) {
            LOG_ERROR << e.what();
            return std::nullopt;
        }
    }

    Json::Value SerializeUserDataToJson(const TUser& userData) {
        Json::Value result;
        result[IdKey] = userData.Id;
        result[NameKey] = userData.Name;
        result[AgeKey] = userData.Age;
        result[SexKey] = userData.Sex;
        result[OrientationKey] = userData.Orientation;
        result[CityKey] = userData.City;
        result[BioKey] = userData.Bio;

        return result;
    }
}
