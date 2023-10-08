#include "config/config.h"
#include "db_adapter/adapter.h"
#include "db_adapter/redis.h"
#include "handlers/handlers.h"

#include <drogon/drogon.h>

#include <auth_lib/auth.h>
#include <server_config/config.h>
#include <utils/json_utils.h>


using namespace auth;
using namespace config;
using namespace db_adapter;
using namespace handlers;
using namespace server_config;
using namespace utils;

void VerifyCondition(bool condition, const std::string& message) {
    if (!condition) {
        LOG_FATAL << message;
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    VerifyCondition(argc == 2, "No config file specified\nUsage: ./mds <config file>");

    const auto configJson = ParseJsonFile(argv[1]);
    VerifyCondition(configJson.has_value(), "Canot parse json from config file");

    const auto config = ParseConfig(configJson.value());
    VerifyCondition(config.has_value(), "Canot parse config file");

    const auto serverConfig = ExtractServerConfigFromJson(configJson.value());
    VerifyCondition(serverConfig.has_value(), "Canot parse config file");

    const auto authorizer = MakeAuthorizer(configJson.value());
    VerifyCondition(authorizer.has_value(), "No telegram token provided");

    const TTableNames tableNames = {
        .UsersTable = config.value().PostgreSQLUsersTable,
    };

    auto postgesqlAdapter = MakePostgeSQLAdapter(
        config.value().PostgreSQLHost,
        config.value().PostgreSQLPort,
        config.value().PostgreSQLDB,
        config.value().PostgreSQLUser,
        config.value().PostgreSQLPassword,
        tableNames
    );

    VerifyCondition(postgesqlAdapter.has_value(), "Canot connect to postgresql database");

    drogon::app().registerSyncAdvice([&authorizer](const drogon::HttpRequestPtr& req) {
        if (!authorizer.value()->IsUserAuthentificated(req->getHeader(InitDataHeaderName))) {
            LOG_ERROR << "User not authorized";
            auto response = drogon::HttpResponse::newHttpResponse();
            response->setCustomStatusCode(403);
            return response;
        }
        return drogon::HttpResponsePtr();
    });

    drogon::app().createRedisClient(config.value().RedisHost, config.value().RedisPort);

    drogon::app().registerHandler(
        "/register",
        [&postgesqlAdapter](const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
            AccountHandler(*postgesqlAdapter.value(), req, std::move(callback), TAccountAction::Create);
        },
        {drogon::Post}
    );

    drogon::app().registerHandler(
        "/edit_account",
        [&postgesqlAdapter](const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback) {
            AccountHandler(*postgesqlAdapter.value(), req, std::move(callback), TAccountAction::Update);
        },
        {drogon::Post}
    );

    drogon::app().registerHandler(
        "/account_info?user_id={user-id}",
        [&postgesqlAdapter](const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback, const std::string& userId) {
            AccountInfoHandler(*postgesqlAdapter.value(), req, std::move(callback), userId);
        },
        {drogon::Get}
    );

    drogon::app().registerHandler(
        "/start?user_id={user-id}",
        [&postgesqlAdapter](const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback, const std::string& userId) {
            StartHanler(*postgesqlAdapter.value(), req, std::move(callback), userId);
        },
        {drogon::Get}
    );

    drogon::app().registerHandler(
        "/search?user_id={user-id}&page={page}",
        [&postgesqlAdapter](const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback, const std::string& userId, uint32_t page) {
            TRedisAdapter redis(drogon::app().getRedisClient());
            SearchHandler(*postgesqlAdapter.value(), req, std::move(callback), userId, redis, page);
        },
        {drogon::Get}
    );

    drogon::app().registerHandler(
        "/like?user_id={user-id}&target_user_id={target-user-id}",
        [](const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback, const std::string& userId, const std::string& targetUserId) {
            TRedisAdapter redis(drogon::app().getRedisClient());
            LikeHandler(req, std::move(callback), redis, userId, targetUserId, false);
        },
        {drogon::Get}
    );

    drogon::app().registerHandler(
        "/dislike?user_id={user-id}&target_user_id={target-user-id}",
        [](const drogon::HttpRequestPtr &req, std::function<void(const drogon::HttpResponsePtr &)> &&callback, const std::string& userId, const std::string& targetUserId) {
            TRedisAdapter redis(drogon::app().getRedisClient());
            LikeHandler(req, std::move(callback), redis, userId, targetUserId, true);
        },
        {drogon::Get}
    );

    LOG_INFO << "Server running on " << serverConfig.value().Host << ":" << serverConfig.value().Port;
    drogon::app().addListener(serverConfig.value().Host, serverConfig.value().Port).run();
}
