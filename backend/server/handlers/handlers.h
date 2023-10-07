#pragma once

#include "db_adapter/adapter.h"
#include "db_adapter/redis.h"

#include <drogon/drogon.h>

#include <functional>

namespace handlers {
    enum class TAccountAction {
        Create,
        Update
    };

    void AccountHandler(
        db_adapter::TPostgreSQLAdapter& adapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        TAccountAction action 
    );

    void AccountInfoHandler(
        db_adapter::TPostgreSQLAdapter& adapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        const std::string& userId
    );

    void StartHanler(
        db_adapter::TPostgreSQLAdapter& adapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        const std::string& userId
    );

    void SearchHandler(
        db_adapter::TPostgreSQLAdapter& adapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        const std::string& userId,
        db_adapter::TRedisAdapter& redisAdapter,
        const uint32_t page
    );
}
