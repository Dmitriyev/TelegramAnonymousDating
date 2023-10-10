#include "auth.h"

#include <openssl/sha.h>
#include <openssl/hmac.h>

#include <utils/json_utils.h>

#include <array>
#include <sstream>
#include <map>
#include <unordered_map>


namespace {
    using namespace utils;

    static const std::string DebugKeyName = "debug_enabled";
    static const std::string HashKey = "hash";
    static const std::string UserKey = "user";
    static const std::string IdKey = "id";

    std::string ToHex(const std::string& str) {
        std::stringstream ss;
    
        ss << std::hex << std::setfill('0');
        for (size_t i = 0; str.length() > i; ++i) {
            ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(str[i]));
        }
    
        return ss.str();
    }

    class TDummyAuthorizer : public auth::IAuthorizer {
    public:
        bool IsUserAuthentificated(const std::string&) const override {
            return true;
        } 

        std::optional<uint64_t> GetUserId(const std::string& initData) const override {
            return std::nullopt;
        }

        std::string GetToken() const override {
            return "";
        }
    };

    class TAuthorizer : public auth::IAuthorizer {
    public:
        TAuthorizer(const std::string& token) 
            : Token(token)
        {
        }

        bool IsUserAuthentificated(const std::string& initData) const override {
            if (initData.empty()) {
                return false;
            }

            const auto initDataParsed = ParseInitData(initData);
            if (!initDataParsed.contains(HashKey)) {
                return false;
            }

            const auto dataCheckString = MakeDataCheckString(initDataParsed);
            const auto hash = initDataParsed.at(HashKey);
            const auto secretKey = CalcHmacSHA256(Token, "WebAppData");

            return ToHex(CalcHmacSHA256(dataCheckString, secretKey)) == hash;
        }
    
    std::optional<uint64_t> GetUserId(const std::string& initData) const override {
        if (initData.empty()) {
            return std::nullopt;
        }
        
        const auto initDataParsed = ParseInitData(initData);
        if (!initDataParsed.contains(UserKey)) {
            return std::nullopt;
        }

        const auto userDataParsed = ParseUserData(initDataParsed.at(UserKey));
        if (!userDataParsed.contains(IdKey)) {
            return std::nullopt;
        }

        return std::stoull(userDataParsed.at(IdKey));
    }

    std::string GetToken() const override {
        return Token;
    }

    private:
        std::string CalcHmacSHA256(const std::string msg, const std::string& decodedKey) const {
            std::array<unsigned char, EVP_MAX_MD_SIZE> hash;
            unsigned int hashLen;
        
            HMAC(
                EVP_sha256(),
                decodedKey.data(),
                static_cast<int>(decodedKey.size()),
                reinterpret_cast<unsigned char const*>(msg.data()),
                static_cast<int>(msg.size()),
                hash.data(),
                &hashLen
            );
        
            return std::string{reinterpret_cast<char const*>(hash.data()), hashLen};
        }

        std::string MakeDataCheckString(const std::map<std::string, std::string>& initDataParsed) const {
            std::stringstream dataCheckString;
            bool isFirst = true;
            for (const auto& [k, v]: initDataParsed) {
                if (k == HashKey) {
                    continue;
                }
                if (!isFirst) {
                    dataCheckString << '\n';
                }
                dataCheckString << k << "=" << v;       
                isFirst = false;
            }

            return dataCheckString.str();
        }

        std::map<std::string, std::string> ParseInitData(const std::string& str) const {
            std::map<std::string, std::string>  result;
            size_t i = 0;
            while (i <= str.size()) {
                const auto equalCharIt = str.find("=", i);
                if (i >= str.size() - 1) {
                    break;
                }
                
                const auto ampersandCharIt = str.find("&", equalCharIt);
                
                result[str.substr(i, equalCharIt - i)] = str.substr(equalCharIt + 1, ampersandCharIt == std::string::npos ? std::string::npos : ampersandCharIt - equalCharIt - 1);
                i = ampersandCharIt == std::string::npos ? std::string::npos : ampersandCharIt + 1;
            }
            
            return result;            
        }

        std::unordered_map<std::string, std::string> ParseUserData(const std::string& rawUserData) const {
            size_t pos = 0;
            const auto isSpeciaSymbol = [&rawUserData, &pos]() {
                const auto ch = rawUserData[pos];
                return ch == '"' || ch == ':' || ch == ',' || ch == '{' || ch == '}';
            };
            const auto parseToken = [&rawUserData, &pos, &isSpeciaSymbol]() {
                const auto begin = pos;
                for (; !isSpeciaSymbol(); ++pos);
                const auto end = pos;
                return std::string(rawUserData.begin() + begin, rawUserData.begin() + end);
            };

            std::unordered_map<std::string, std::string> result;
            while (pos < rawUserData.size()) {
                if (isSpeciaSymbol()) {
                    ++pos;
                    continue;
                }
                const auto key = parseToken();
                for (; isSpeciaSymbol(); ++pos);
                const auto value = parseToken();
                result.emplace(key, value);
            }
            return result;
        }

    private:
        const std::string Token;
    };
}

namespace auth {
    std::optional<TAuthorizerPtr> MakeAuthorizer(const Json::Value& configJson) {
        if (configJson.isMember(DebugKeyName) && configJson[DebugKeyName].isBool() && configJson[DebugKeyName].asBool()) {
            return std::make_unique<TDummyAuthorizer>();
        }

        try {
            const auto token = GetStringValueFromJson(configJson, "telegram_token");
            return std::make_unique<TAuthorizer>(token);
        } catch (const std::exception& e) {
            return std::nullopt;
        }
    }    
}
