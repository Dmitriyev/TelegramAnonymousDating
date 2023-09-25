#include "handlers.h"

namespace handlers {
    using namespace drogon;

    void RegisterHandler(const HttpRequestPtr& req, std::function<void(const HttpResponsePtr&)>&& callback) {
        auto resp = HttpResponse::newHttpResponse();
        const auto reqBody = req->getJsonObject();
        if (!reqBody) {
            resp->setBody("Incorrect params");
            resp->setCustomStatusCode(400);
            LOG_INFO << "Error";
        } else {
            LOG_INFO << reqBody->toStyledString();
            resp->setBody("Hello!");
        }
        callback(resp);
    }
}
