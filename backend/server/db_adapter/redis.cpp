#include "redis.h"

namespace {
    inline std::string FormatKey(const std::string& objectType, common::TUserId userId, const std::string& field) {
        std::stringstream ss;
        ss << objectType << ":" << userId << ":" << field;
        return ss.str();
    }
} // namespace

namespace db_adapter {
    TRedisAdapter::TRedisAdapter(RedisClientPtr redisClient)
        : RedisClient(redisClient) { }

    void TRedisAdapter::SetLike(common::TUserId userId, common::TUserId targetUserId) {
        const auto userLikesKey = FormatKey("user", userId, "likes");
        const auto targetUserLikesKey = FormatKey("user", targetUserId, "likes_me");
        
        RedisClient->execCommandAsync(
            [](const drogon::nosql::RedisResult&) {},
            [&](const std::exception &err) {
                LOG_ERROR << "Failed lpush " << userLikesKey << " " << targetUserId;
            },
            "lpush %s %s",
            userLikesKey.c_str(),
            targetUserId
        );

        RedisClient->execCommandAsync(
            [](const drogon::nosql::RedisResult&) {},
            [&](const std::exception &err) {
                LOG_ERROR << "Failed lpush " << targetUserLikesKey << " " << userId;
            },
            "lpush %s %d",
            targetUserLikesKey.c_str(),
            userId
        );
    }

    void TRedisAdapter::SetDislike(common::TUserId userId, common::TUserId targetUserId) {
        const auto userDislikesKey = FormatKey("user", userId, "dislikes");
        const auto targetUserDislikesKey = FormatKey("user", targetUserId, "dislike_me");
        LOG_ERROR << "LPUSH " << userDislikesKey << " " << targetUserDislikesKey;
        
        RedisClient->execCommandAsync(
            [](const drogon::nosql::RedisResult&) {},
            [&](const std::exception &err) {
                LOG_ERROR << "Failed lpush " << userDislikesKey << " " << targetUserId;
            },
            "lpush %s %d",
            userDislikesKey.c_str(),
            targetUserId
        );

        RedisClient->execCommandAsync(
            [](const drogon::nosql::RedisResult&) {},
            [&](const std::exception &err) {
                LOG_ERROR << "Failed lpush " << targetUserDislikesKey << " " << userId;
            },
            "lpush %s %d",
            targetUserDislikesKey.c_str(),
            userId
        );
    }

    std::vector<common::TUserId> TRedisAdapter::GetLikesMe(common::TUserId userId) {
        const auto userLikesMeKey = FormatKey("user", userId, "likes_me");
        
        std::vector<common::TUserId> result;
        auto status = RedisClient->execCommandSync<bool>(
            [&](const RedisResult &r) {
                if (r.type() != drogon::nosql::RedisResultType::kArray) {
                    LOG_ERROR << "Wrong likes me type";
                    return false;
                }
                const auto array = r.asArray();
                for (const auto& item : array) {
                    result.push_back(std::stoull(item.asString()));
                }
                return true;
            },
            "lrange %s 0 -1",
            userLikesMeKey.c_str()
        );

        return result;
    }

    std::vector<common::TUserId> TRedisAdapter::GetViewedUserIds(common::TUserId userId) {
        const auto userLikesKey = FormatKey("user", userId, "likes");
        const auto userDislikesKey = FormatKey("user", userId, "dislikes");
        
        std::vector<common::TUserId> result;
        auto status = RedisClient->execCommandSync<bool>(
            [&](const RedisResult &r) {
                if (r.type() != drogon::nosql::RedisResultType::kArray) {
                    LOG_ERROR << "Wrong likes type";
                    return false;
                }
                const auto array = r.asArray();
                for (const auto& item : array) {
                    result.push_back(std::stoull(item.asString()));
                }
                return true;
            },
            "lrange %s 0 -1",
            userLikesKey.c_str()
        );
        status = RedisClient->execCommandSync<bool>(
            [&](const RedisResult &r) {
                if (r.type() != drogon::nosql::RedisResultType::kArray) {
                    LOG_ERROR << "Wrong dislikes type";
                    return false;
                }
                const auto array = r.asArray();
                for (const auto& item : array) {
                    result.push_back(std::stoull(item.asString()));
                }
                return true;
            },
            "lrange %s 0 -1",
            userDislikesKey.c_str()
        );
        return result;
    }
} // namespace db_adapter
