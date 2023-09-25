#pragma once

#include <drogon/drogon.h>

#include <functional>

namespace handlers {
    void RegisterHandler(const drogon::HttpRequestPtr& req, std::function<void(const drogon::HttpResponsePtr&)>&& callback);
}
