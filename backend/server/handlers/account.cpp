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
        TAccountAction action
    ) {
        auto resp = HttpResponse::newHttpResponse();
        const auto reqBody = req->getJsonObject();
        if (!reqBody) {
            LOG_ERROR << "No json passed in request";
            resp->setCustomStatusCode(400);
            callback(resp);
            return;
        }

        const auto user = ExtractUserDataFromJson(*reqBody);
        if (!user.has_value()) {
            LOG_ERROR << "Incorrect user json data";
            resp->setCustomStatusCode(400);
            callback(resp);
            return;
        }

        bool res = false;
        if (action == TAccountAction::Create) {
            res = adapter.InsertUserData(user.value());
        } else if (action == TAccountAction::Update) {
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
}
