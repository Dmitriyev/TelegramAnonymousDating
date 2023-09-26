#pragma once

#include "common/common_structures.h"

#include <pqxx/pqxx>

#include <memory>
#include <optional>
#include <string>


namespace db_adapter {
    struct TTableNames {
        std::string UsersTable;
    };

    class TPostgreSQLAdapter {
    public:
        TPostgreSQLAdapter(const std::string& connectionOptions, const TTableNames& tableNames);

        bool WriteUserData(const common::TUser& user, bool rewriteRow = false);

    private:
        pqxx::connection Connection;
        TTableNames TableNames;
    };

    using TPostgreSQLAdapterPtr = std::unique_ptr<TPostgreSQLAdapter>;

    std::optional<TPostgreSQLAdapterPtr> MakePostgeSQLAdapter(
        const std::string& host,
        const std::string& dbName,
        const std::string& user,
        const std::string& password,
        const TTableNames& tableNames
    );
}
