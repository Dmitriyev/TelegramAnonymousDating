#include "handlers.h"
#include "common/common_structures.h"
#include "utils/json_utils.h"

#include <drogon/drogon.h>

#include <algorithm>

namespace handlers {
    using namespace common;
    using namespace db_adapter;

    void SendMatchMessage(
        drogon::HttpClientPtr client,
        TUserId userId1,
        TUserId userId2
    ) {
        auto prepareReq = [](TUserId userId, TUserId matchWithUserId) {
            auto req = drogon::HttpRequest::newHttpRequest();
            req->setMethod(drogon::Get);
            req->setPath("/sendMessage");
            req->setParameter("chat_id", std::to_string(userId));
            std::stringstream matchTextSs;
            matchTextSs << "Hello! Match with " << matchWithUserId;
            req->setParameter("text", matchTextSs.str());
            return req;
        };
        client->sendRequest(prepareReq(userId1, userId2), [](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {});
        client->sendRequest(prepareReq(userId2, userId1), [](drogon::ReqResult result, const drogon::HttpResponsePtr &response) {});
    }

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
        drogon::HttpClientPtr client,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        db_adapter::TRedisAdapter& redisAdapter,
        const std::string& whoLikedId,
        const std::string& targetLikeId,
        std::optional<uint64_t> tgUserId,
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
            const auto userIdLikesMe = redisAdapter.GetLikesMe(whoLikedUIntId);
            if (std::find(userIdLikesMe.begin(), userIdLikesMe.end(), targetLikeUIntId) != userIdLikesMe.end()) {
                SendMatchMessage(client, whoLikedUIntId, targetLikeUIntId);
            }
        }
        callback(resp);
    }
} // namespace handlers
