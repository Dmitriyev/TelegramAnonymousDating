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
        TAccountAction action,
        common::TUserId tgUserId,
        db_adapter::TRedisAdapter redisAdapter
    );

    void AccountInfoHandler(
        db_adapter::TPostgreSQLAdapter& adapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        const std::string& userId
    );

    void StartHanler(
        db_adapter::TRedisAdapter& redisAdapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        const std::optional<uint64_t> userId
    );

    void SearchHandler(
        db_adapter::TPostgreSQLAdapter& adapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        const std::string& userId,
        db_adapter::TRedisAdapter& redisAdapter,
        const uint32_t page
    );

    void LikeHandler(
        const drogon::HttpRequestPtr& req,
        drogon::HttpClientPtr client,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        db_adapter::TRedisAdapter& redisAdapter,
        const std::string& whoLikedId,
        const std::string& targetLikeId,
        std::optional<uint64_t> tgUserId,
        bool dislike
    );
}
