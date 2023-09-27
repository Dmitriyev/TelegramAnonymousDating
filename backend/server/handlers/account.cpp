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
            resp->setBody("Incorrect params");
            resp->setCustomStatusCode(400);
            LOG_ERROR << "No json passed in request";
            callback(resp);
            return;
        }

        const auto user = ExtractUserDataFromJson(*reqBody);
        if (!user.has_value()) {
            resp->setBody("Incorrect params");
            resp->setCustomStatusCode(400);
            LOG_ERROR << "Incorrect user json data";
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
            resp->setCustomStatusCode(500);
            LOG_ERROR << "Error writing database";
            callback(resp);
            return;
        }

        callback(resp);
    }
}
