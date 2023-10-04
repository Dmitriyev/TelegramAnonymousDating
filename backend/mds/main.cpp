#include "aws_adapter/adapter.h"
#include "config/config.h"
#include "handlers/handlers.h"

#include <drogon/drogon.h>


using namespace aws_adapter;
using namespace config;
using namespace drogon;
using namespace handlers;

int main(int argc, char* argv[])
{
    if (argc != 2) {
        LOG_FATAL << "No config file specified\nUsage: ./mds <config file>";
        exit(1);
    }

    const auto config = ParseConfig(argv[1]);
    if (!config.has_value()) {
        LOG_FATAL << "Canot parse config file";
        exit(1);
    }

    TAdapter adapter(
        config.value().CloudRegion,
        config.value().CloudEndpoint,
        config.value().CloudKeyId,
        config.value().CloudKey,
        config.value().CloudBucket
    );

    app().registerHandler(
        "/upload?user_id={user-id}&format={format}&md5={md5}",
        [&adapter](
            const HttpRequestPtr &req,
            std::function<void(const HttpResponsePtr &)> &&callback,
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
        {Post}
    );

    app().registerHandler(
        "/avatar?id={id}",
        [&adapter](
            const HttpRequestPtr &req,
            std::function<void(const HttpResponsePtr &)> &&callback,
            const std::string& id
        ) {
            GetHandler(
                adapter,
                req,
                std::move(callback),
                id
            );
        },
        {Get}
    );


    LOG_INFO << "Server running on " << config.value().ServerHost << ":" << config.value().ServerPort;
    app().addListener(config.value().ServerHost, config.value().ServerPort).run();
    return 0;
}

