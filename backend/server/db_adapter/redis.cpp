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
            userLikesKey,
            std::to_string(targetUserId)
        );

        RedisClient->execCommandAsync(
            [](const drogon::nosql::RedisResult&) {},
            [&](const std::exception &err) {
                LOG_ERROR << "Failed lpush " << targetUserLikesKey << " " << userId;
            },
            "lpush %s %s",
            targetUserLikesKey,
            std::to_string(userId)
        );
    }

    void TRedisAdapter::SetDislike(common::TUserId userId, common::TUserId targetUserId) {
        const auto userDislikesKey = FormatKey("user", userId, "dislikes");
        const auto targetUserDislikesKey = FormatKey("user", targetUserId, "dislike_me");
        
        RedisClient->execCommandAsync(
            [](const drogon::nosql::RedisResult&) {},
            [&](const std::exception &err) {
                LOG_ERROR << "Failed lpush " << userDislikesKey << " " << targetUserId;
            },
            "lpush %s %s",
            userDislikesKey,
            std::to_string(targetUserId)
        );

        RedisClient->execCommandAsync(
            [](const drogon::nosql::RedisResult&) {},
            [&](const std::exception &err) {
                LOG_ERROR << "Failed lpush " << targetUserDislikesKey << " " << userId;
            },
            "lpush %s %s",
            targetUserDislikesKey,
            std::to_string(userId)
        );
    }

    std::vector<common::TUserId> TRedisAdapter::GetViewedUserIds(common::TUserId userId) {
        const auto userLikesKey = FormatKey("user", userId, "likes");
        const auto userDislikesKey = FormatKey("user", userId, "dislikes");
        
        std::vector<common::TUserId> result;
        auto status = RedisClient->execCommandSync<bool>(
            [&](const RedisResult &r) {
                const auto array = r.asArray();
                for (const auto& item : array) {
                    result.push_back(item.asInteger());
                }
                return true;
            },
            "lrange %s 0 -1",
            userLikesKey.c_str()
        );
        status = RedisClient->execCommandSync<bool>(
            [&](const RedisResult &r) {
                const auto array = r.asArray();
                for (const auto& item : array) {
                    result.push_back(item.asInteger());
                }
                return true;
            },
            "lrange %s 0 -1",
            userDislikesKey.c_str()
        );
        return result;
    }
} // namespace db_adapter
