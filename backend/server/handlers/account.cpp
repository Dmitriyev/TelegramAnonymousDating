#include "handlers.h"
#include "common/common_structures.h"


namespace handlers {
    using namespace common;
    using namespace db_adapter;
    using namespace drogon;

    void AccountHandler(
        TPostgreSQLAdapter& adapter,
        const HttpRequestPtr& req,
        std::function<void(const HttpResponsePtr&)>&& callback,
        TAccountAction action,
        common::TUserId tgUserId,
        db_adapter::TRedisAdapter redisAdapter
    ) {
        auto resp = HttpResponse::newHttpResponse();
        const auto reqBody = req->getJsonObject();
        if (!reqBody) {
            LOG_ERROR << "No json passed in request";
            resp->setCustomStatusCode(400);
            callback(resp);
            return;
        }

        auto user = ExtractUserDataFromJson(*reqBody);
        if (!user.has_value()) {
            LOG_ERROR << "Incorrect user json data";
            resp->setCustomStatusCode(400);
            callback(resp);
            return;
        }

        bool res = false;
        if (action == TAccountAction::Create) {
            auto userId = redisAdapter.ConvertTgUserIdToUserId(tgUserId, true);
            if (!userId.has_value()) {
                LOG_ERROR << "tgUserId to userId connvertation error";
                resp->setCustomStatusCode(500);
                callback(resp);
                return;
            }
            user->Id = userId.value();
            res = adapter.InsertUserData(user.value());
        } else if (action == TAccountAction::Update) {
            auto userId = redisAdapter.ConvertTgUserIdToUserId(tgUserId);
            if (!userId.has_value()) {
                LOG_ERROR << "user not registered";
                resp->setCustomStatusCode(400);
                callback(resp);
                return;
            }
            if (userId.value() != user->Id) {
                LOG_ERROR << "difference between init data user id and json";
                resp->setCustomStatusCode(400);
                callback(resp);
                return;
            }
            res = adapter.UpdateUserData(user.value());
        } else {
            LOG_ERROR << "Unknown account action";
        }

        if (!res) {
            LOG_ERROR << "Error writing database";
            resp->setCustomStatusCode(500);
            callback(resp);
            return;
        }

        Json::Value result;
        result["user_id"] = user->Id;
        resp = toResponse(result);
        callback(resp);
    }

    void AccountInfoHandler(
        db_adapter::TPostgreSQLAdapter& adapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        const std::string& userId
    ) {
        auto resp = HttpResponse::newHttpResponse();

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

        const auto resultJson = SerializeUserDataToJson(userData.value());
        resp = toResponse(resultJson);
        callback(resp);
    }

    void StartHanler(
        db_adapter::TRedisAdapter& redisAdapter,
        const drogon::HttpRequestPtr& req,
        std::function<void(const drogon::HttpResponsePtr&)>&& callback,
        const std::string& tgUserId
    ) {
        auto resp = HttpResponse::newHttpResponse();

        TUserId tgUserIdUInt = 0;
        try {
            tgUserIdUInt = std::stoull(tgUserId);
        } catch (const std::exception& e) {
            LOG_ERROR << "Canot parse userId " << tgUserId;
            resp->setCustomStatusCode(400);
            callback(resp);
            return;
        }

        const auto userId = redisAdapter.ConvertTgUserIdToUserId(tgUserIdUInt);
        if (!userId.has_value()) {
            LOG_ERROR << "Canot check account existance " << tgUserId;
            resp->setCustomStatusCode(500);
            callback(resp);
            return;
        }

        Json::Value result;
        result["user_registred"] = userId.has_value();
        if (userId.has_value()) {
            result["user_id"] = userId.value();
        }
        resp = toResponse(result);
        callback(resp);
    }
}
