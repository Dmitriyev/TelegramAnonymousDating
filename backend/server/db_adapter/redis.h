#pragma once

#include "common/common_structures.h"

#include <drogon/drogon.h>

namespace db_adapter {
    using namespace drogon::nosql;

    class TRedisAdapter {
    public:
        TRedisAdapter(RedisClientPtr redisClient);

        void SetLike(common::TUserId userId, common::TUserId targetUserId);
        void SetDislike(common::TUserId userId, common::TUserId targetUserId);
        
        // std::vector<common::TUserId> GetLikes(common::TUserId userId);
        // std::vector<common::TUserId> GetDislikes(common::TUserId userId);

        std::vector<common::TUserId> GetViewedUserIds(common::TUserId userId);
    private:
        RedisClientPtr RedisClient;
    };

} // namespace db_adapter
