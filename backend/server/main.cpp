#include "handlers/handlers.h"
#include <drogon/drogon.h>

using namespace drogon;
using namespace handlers;

int main() {
    app().registerHandler(
        "/register",
        [](const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
            RegisterHandler(req, std::move(callback));
        },
        {Post});

    LOG_INFO << "Server running on 127.0.0.1:8848";
    app().addListener("127.0.0.1", 8848).run();
}
