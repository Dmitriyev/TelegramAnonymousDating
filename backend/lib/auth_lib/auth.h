#pragma once

#include <json/json.h>

#include <string>
#include <memory>
#include <optional>


namespace auth {
    static const std::string InitDataHeaderName = "x-telegram-init-data";

    class IAuthorizer {
    public:
        virtual ~IAuthorizer() = default;

        virtual bool IsUserAuthentificated(const std::string& initData) const = 0;
    };

    using TAuthorizerPtr = std::unique_ptr<IAuthorizer>;

    std::optional<TAuthorizerPtr> MakeAuthorizer(const Json::Value& configJson);
}

