#include "handlers.h"
#include "common/common_structures.h"
#include "utils/json_utils.h"

#include <algorithm>

namespace handlers {
    using namespace common;
    using namespace db_adapter;

    void SearchHandler(
        TPostgreSQLAdapter& adapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        const std::string& userId,
        db_adapter::TRedisAdapter& redisAdapter,
        const uint32_t page
    ) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        
        TUserId userIdUInt = 0;
        try {
            userIdUInt = std::stoull(userId);
        } catch (const std::exception& e) {
            LOG_ERROR << "Canot parse userId " << userId;
            resp->setCustomStatusCode(400);
            callback(resp);
            return;
        }

        const auto userData = adapter.GetAccountInfo(userIdUInt);
        if (!userData.has_value()) {
            LOG_ERROR << "Canot read account indormation " << userId;
            resp->setCustomStatusCode(500);
            callback(resp);
            return;
        }

        LOG_ERROR << "REDIS /start";
        const auto viewedUserIds = redisAdapter.GetViewedUserIds(userIdUInt);
        LOG_ERROR << "REDIS /end";
        const auto candidates = adapter.GetMatchCandidates(userData.value(), page);
        std::vector<common::TUserId> filteredCandidates;
        for (const auto& user : candidates) {
            if (std::find(viewedUserIds.begin(), viewedUserIds.end(), user.Id) == viewedUserIds.end()) {
                filteredCandidates.push_back(user.Id);
            }
        }
        Json::Value result;
        result["search"] = utils::ToJson(filteredCandidates);
        resp = drogon::toResponse(result);
        callback(resp);
    }

    void LikeHandler(
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        db_adapter::TRedisAdapter& redisAdapter,
        const std::string& whoLikedId,
        const std::string& targetLikeId,
        bool dislike
    ) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        
        TUserId whoLikedUIntId = 0;
        try {
            whoLikedUIntId = std::stoull(whoLikedId);
        } catch (const std::exception& e) {
            LOG_ERROR << "Canot parse userId " << whoLikedId;
            resp->setCustomStatusCode(400);
            callback(resp);
            return;
        }
        
        TUserId targetLikeUIntId = 0;
        try {
            targetLikeUIntId = std::stoull(targetLikeId);
        } catch (const std::exception& e) {
            LOG_ERROR << "Canot parse userId " << targetLikeId;
            resp->setCustomStatusCode(400);
            callback(resp);
            return;
        }

        if (dislike) {
            redisAdapter.SetDislike(whoLikedUIntId, targetLikeUIntId);
        } else {
            redisAdapter.SetLike(whoLikedUIntId, targetLikeUIntId);
        }
        callback(resp);
    }
} // namespace handlers
