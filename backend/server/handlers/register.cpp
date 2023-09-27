#include "handlers.h"
#include "common/common_structures.h"

namespace handlers {
    using namespace common;
    using namespace drogon;
    using namespace db_adapter;

    void RegisterHandler(
        TPostgreSQLAdapter& adapter,
        const HttpRequestPtr& req,
        std::function<void(const HttpResponsePtr&)>&& callback
    ) {
        auto resp = HttpResponse::newHttpResponse();
        const auto reqBody = req->getJsonObject();
        if (!reqBody) {
            resp->setBody("Incorrect params");
            resp->setCustomStatusCode(400);
            LOG_ERROR << "No json passed in request. /register method";
            callback(resp);
            return;
        }

        const auto user = ExtractUserDataFromJson(*reqBody);
        if (!user.has_value()) {
            resp->setBody("Incorrect params");
            resp->setCustomStatusCode(400);
            LOG_ERROR << "Incorrect user json data. /register method";
            callback(resp);
            return;
        }

        if (!adapter.WriteUserData(user.value())) {
            resp->setCustomStatusCode(500);
            LOG_ERROR << "Error writing database. /register method";
            callback(resp);
            return;
        }

        callback(resp);
    }
}
