#include "aws_adapter/adapter.h"
#include "config/config.h"
#include "handlers/handlers.h"

#include <drogon/drogon.h>

#include <server_config/config.h>
#include <utils/json_utils.h>


using namespace aws_adapter;
using namespace config;
using namespace handlers;
using namespace utils;
using namespace server_config;

void VerifyCondition(bool condition, const std::string& message) {
    if (!condition) {
        LOG_FATAL << message;
        exit(1);
    }
}

int main(int argc, char* argv[])
{
    VerifyCondition(argc == 2, "No config file specified\nUsage: ./mds <config file>");
    
    const auto configJson = ParseJsonFile(argv[1]);
    VerifyCondition(configJson.has_value(), "Canot parse json from config file");

    const auto config = ParseConfig(configJson.value());
    VerifyCondition(config.has_value(), "Canot parse config file");

    const auto serverConfig = ExtractServerConfigFromJson(configJson.value());
    VerifyCondition(serverConfig.has_value(), "Canot parse config file");

    TAdapter adapter(
        config.value().CloudRegion,
        config.value().CloudEndpoint,
        config.value().CloudKeyId,
        config.value().CloudKey,
        config.value().CloudBucket
    );

    drogon::app().registerHandler(
        "/upload?user_id={user-id}&format={format}&md5={md5}",
        [&adapter](
            const drogon::HttpRequestPtr &req,
            std::function<void(const drogon::HttpResponsePtr &)> &&callback,
            const std::string& userId,
            const std::string& format,
            const std::string& md5
        ) {
            UploadHandler(
                adapter,
                req,
                std::move(callback),
                userId,
                format,
                md5
            );
        },
        {drogon::Post}
    );

    drogon::app().registerHandler(
        "/avatar?id={id}",
        [&adapter](
            const drogon::HttpRequestPtr &req,
            std::function<void(const drogon::HttpResponsePtr &)> &&callback,
            const std::string& id
        ) {
            GetHandler(
                adapter,
                req,
                std::move(callback),
                id
            );
        },
        {drogon::Get}
    );

    LOG_INFO << "Server running on " << serverConfig.value().Host << ":" << serverConfig.value().Port;
    drogon::app().addListener(serverConfig.value().Host, serverConfig.value().Port).run();
    return 0;
}

