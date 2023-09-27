#include "adapter.h"

#include <trantor/utils/Logger.h>

#include <sstream>


namespace db_adapter {
    TPostgreSQLAdapter::TPostgreSQLAdapter(const std::string& connectionOptions, const TTableNames& tableNames)
        : Connection(std::move(connectionOptions))
        , TableNames(tableNames)
    {
    }

    bool TPostgreSQLAdapter::InsertUserData(const common::TUser& user) {
        pqxx::work work(Connection);
        try {
            std::stringstream insertCommand;
            insertCommand << "INSERT INTO " << TableNames.UsersTable << " VALUES (" <<
                user.Id << ", " <<
                "'" << user.Name << "', " <<
                user.Age << ", " <<
                user.Sex << ", " <<
                user.Orientation << ", " <<
                "'" << user.City << "', " <<
                "'" << user.Bio << "');";

            LOG_INFO << insertCommand.str();
            work.exec0(insertCommand.str());
            work.commit();
            return true;
                
        } catch (const std::exception& e) {
            LOG_ERROR << "Canot write user data into table " << TableNames.UsersTable << ". " << e.what();
            work.abort();
            return false;
        }
    }

    bool TPostgreSQLAdapter::UpdateUserData(const common::TUser& user) {
        pqxx::work work(Connection);
        try {
            std::stringstream updateCommand;
            updateCommand << "UPDATE " << TableNames.UsersTable << " SET " <<
                "username = '" << user.Name << "', " <<
                "age = " << user.Age << ", " <<
                "sex = " << user.Sex << ", " <<
                "orientation = " << user.Orientation << ", " <<
                "city = '" << user.City << "', " <<
                "bio = '" << user.Bio << "' " <<
                "WHERE id = " << user.Id << ";";

            LOG_INFO << updateCommand.str();
            work.exec0(updateCommand.str());
            work.commit();
            return true;
                
        } catch (const std::exception& e) {
            LOG_ERROR << "Canot update user data at table " << TableNames.UsersTable << ". " << e.what();
            work.abort();
            return false;
        }
    }

    std::optional<TPostgreSQLAdapterPtr> MakePostgeSQLAdapter(
        const std::string& host, 
        const std::string& dbName,
        const std::string& user,
        const std::string& password,
        const TTableNames& tableNames
    ) {
        std::stringstream coonectionOptions;
        coonectionOptions << "host=" << host << " dbname=" << dbName << " user=" << user << " password=" << password;
        try {
            return std::make_unique<TPostgreSQLAdapter>(coonectionOptions.str(), tableNames);
        } catch (const std::exception &e) {
            LOG_ERROR << e.what();
            return std::nullopt;
        }
    }
}

