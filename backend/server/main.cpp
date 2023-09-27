#include "config/config.h"
#include "db_adapter/adapter.h"
#include "handlers/handlers.h"

#include <drogon/drogon.h>

using namespace config;
using namespace db_adapter;
using namespace drogon;
using namespace handlers;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        LOG_FATAL << "No config file specified\nUsage: ./server <config file>";
        exit(1);
    }

    const auto config = ParseConfig(argv[1]);
    if (!config.has_value()) {
        LOG_FATAL << "Canot parse config file";
        exit(1);
    }

    const TTableNames tableNames = {
        .UsersTable = config.value().PostgreSQLUsersTable,
    };

    auto postgesqlAdapter = MakePostgeSQLAdapter(
        config.value().PostgreSQLHost,
        config.value().PostgreSQLDB,
        config.value().PostgreSQLUser,
        config.value().PostgreSQLPassword,
        tableNames
    );

    if (!postgesqlAdapter.has_value()) {
        LOG_FATAL << "Canot connect to postgresql database";
        exit(1);
    }

    app().registerHandler(
        "/register",
        [&postgesqlAdapter](const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
            AccountHandler(*postgesqlAdapter.value(), req, std::move(callback), TAccountAction::Create);
        },
        {Post}
    );

    app().registerHandler(
        "/edit_account",
        [&postgesqlAdapter](const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
            AccountHandler(*postgesqlAdapter.value(), req, std::move(callback), TAccountAction::Update);
        },
        {Post}
    );

    LOG_INFO << "Server running on 127.0.0.1:8848";
    app().addListener(config.value().ServerHost, config.value().ServerPort).run();
}
