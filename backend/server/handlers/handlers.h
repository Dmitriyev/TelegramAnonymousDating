#pragma once

#include "db_adapter/adapter.h"

#include <drogon/drogon.h>

#include <functional>

namespace handlers {
    void RegisterHandler(
        db_adapter::TPostgreSQLAdapter& adapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback
    );
}
