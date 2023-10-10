#include "redis.h"

namespace {
    static const std::string UserCounterKey = "UserCounter";

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

    
    std::optional<common::TUserId> TRedisAdapter::ConvertTgUserIdToUserId(common::TUserId tgUserId, bool createIfNotExist) {
        const auto tgUserIdToUserIdKey = FormatKey("tg_user", tgUserId, "user_id");
        auto userId = RedisClient->execCommandSync<std::optional<common::TUserId>>(
            [&](const RedisResult &r) -> std::optional<common::TUserId> {
                if (r.type() == drogon::nosql::RedisResultType::kNil) {
                    LOG_ERROR << "Can't find user with tgId = " << tgUserId;
                    return std::nullopt;
                }
                return std::stoull(r.asString());
            },
            "get %s",
            tgUserIdToUserIdKey.c_str()
        );
        if (createIfNotExist && !userId.has_value()) {
            userId = RedisClient->execCommandSync<std::optional<common::TUserId>>(
                [](const RedisResult &r) -> std::optional<common::TUserId> {
                    if (r.type() != drogon::nosql::RedisResultType::kInteger) {
                        LOG_ERROR << "Smth went wrong with UserCounter";
                        return std::nullopt;
                    }
                    return r.asInteger();
                },
                "INCR %s",
                UserCounterKey.c_str()
            );
            if (userId.has_value()) {
                auto statusOk = RedisClient->execCommandSync<bool>(
                    [](const RedisResult &r) {
                        return r.type() == drogon::nosql::RedisResultType::kString && r.asString() == "OK";
                    },
                    "set %s %d",
                    tgUserIdToUserIdKey.c_str(),
                    userId.value()
                );
                if (statusOk) {
                    const auto userIdToTgUserIdKey = FormatKey("user", userId.value(), "tg_user_id");
                    statusOk = RedisClient->execCommandSync<bool>(
                        [](const RedisResult &r) {
                            return r.type() == drogon::nosql::RedisResultType::kString && r.asString() == "OK";
                        },
                        "set %s %d",
                        userIdToTgUserIdKey.c_str(),
                        tgUserId
                    );
                }
                if (!statusOk) {
                    return std::nullopt;
                }
            }
        }
        return userId;
    }
    std::optional<common::TUserId> TRedisAdapter::ConvertUserIdToTgUserId(common::TUserId userId) {
        const auto userIdToTgUserIdKey = FormatKey("user", userId, "tg_user_id");
        auto tgUserId = RedisClient->execCommandSync<std::optional<common::TUserId>>(
            [&](const RedisResult &r) -> std::optional<common::TUserId> {
                if (r.type() == drogon::nosql::RedisResultType::kNil) {
                    LOG_ERROR << "Can't find user with Id = " << userId;
                    return std::nullopt;
                }
                return std::stoull(r.asString());
            },
            "get %s",
            userIdToTgUserIdKey.c_str()
        );
        return tgUserId;
    }
} // namespace db_adapter
