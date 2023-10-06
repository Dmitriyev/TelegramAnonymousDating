#pragma once

#include <string>
#include <memory>


namespace auth {
    class IAuthorizer {
    public:
        virtual ~IAuthorizer() = default;

        public bool IsUserAuthorized(const std::string& initData);
    };

    using TAuthorizerPtr = std::unique_ptr<IAuthorizer>;

    TAuthorizerPtr
}

