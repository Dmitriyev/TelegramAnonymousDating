#include "adapter.h"

#include <trantor/utils/Logger.h>

#include <sstream>

namespace {
    // Column names
    static const std::string IdCol = "id";

    enum EColumnIndexes {
        Id = 0,
        Name,
        Age,
        Sex,
        Orientation,
        City,
        Bio,
        Avatars,
    };

    std::string StringVectorToPostgreSQLFormat(const std::vector<std::string>& stringVector) {
        std::stringstream result;
        result << "'{";

        bool isFirst = true;
        for (const auto& str: stringVector) {
            if (!isFirst) {
                result << ", ";
            }

            result << "\"" << str << "\"";
            isFirst = false;
        }
        result << "}'";

        return result.str();
    }

    std::vector<std::string> ConvertPQXXArrayToVector(const pqxx::row::reference& field) {
        std::vector<std::string> result;
        auto array = field.as_array();

        std::pair<pqxx::array_parser::juncture, std::string> elem;
        do
        {
            elem = array.get_next();
            if (elem.first == pqxx::array_parser::juncture::string_value) {
                result.push_back(elem.second);
            }
        }
        while (elem.first != pqxx::array_parser::juncture::done);

        return result;
    }
}

namespace db_adapter {
    using namespace common;

    TPostgreSQLAdapter::TPostgreSQLAdapter(const std::string& connectionOptions, const TTableNames& tableNames)
        : Connection(std::move(connectionOptions))
        , TableNames(tableNames)
    {
    }

    bool TPostgreSQLAdapter::InsertUserData(const TUser& user) {
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
                "'" << user.Bio << "', " <<
                StringVectorToPostgreSQLFormat(user.Avatars) << ");";

            work.exec0(insertCommand.str());
            work.commit();
            return true;
        } catch (const std::exception& e) {
            LOG_ERROR << "Canot write user data into table " << TableNames.UsersTable << ". " << e.what();
            work.abort();
            return false;
        }
    }

    bool TPostgreSQLAdapter::UpdateUserData(const TUser& user) {
        pqxx::work work(Connection);
        try {
            std::stringstream updateCommand;
            updateCommand << "UPDATE " << TableNames.UsersTable << " SET " <<
                "username = '" << user.Name << "', " <<
                "age = " << user.Age << ", " <<
                "sex = " << user.Sex << ", " <<
                "orientation = " << user.Orientation << ", " <<
                "city = '" << user.City << "', " <<
                "bio = '" << user.Bio << "', " <<
                "avatars = " << StringVectorToPostgreSQLFormat(user.Avatars) << " " <<
                "WHERE " << IdCol << " =  " << user.Id << ";";

            work.exec0(updateCommand.str());
            work.commit();
            return true;
        } catch (const std::exception& e) {
            LOG_ERROR << "Canot update user data at table " << TableNames.UsersTable << ". " << e.what();
            work.abort();
            return false;
        }
    }

    std::optional<TUser> TPostgreSQLAdapter::GetAccountInfo(TUserId userId) {
        pqxx::work work(Connection);
        try {
            std::stringstream selectCommand;
            selectCommand << "SELECT * FROM " << TableNames.UsersTable << " WHERE " << IdCol << " = " << userId;

            const auto res = work.exec(selectCommand.str());

            if (res.size() != 1) {
                LOG_ERROR << "No user data for user id " << userId << " in " << TableNames.UsersTable << " table";
                return std::nullopt;
            } else if (res[0].size() != TUser::FieldsCount) {
                LOG_ERROR << "Wrong table schema in " << TableNames.UsersTable << " table";
                return std::nullopt;
            }

            const auto& row = res[0];

            TUser userData {
                .Id = row[EColumnIndexes::Id].as<decltype(TUser::Id)>(),
                .Name = row[EColumnIndexes::Name].as<decltype(TUser::Name)>(),
                .Age = row[EColumnIndexes::Age].as<decltype(TUser::Age)>(),
                .Sex = row[EColumnIndexes::Sex].as<decltype(TUser::Sex)>(),
                .Orientation = row[EColumnIndexes::Orientation].as<decltype(TUser::Orientation)>(),
                .City = row[EColumnIndexes::City].as<decltype(TUser::City)>(),
                .Bio = row[EColumnIndexes::Bio].as<decltype(TUser::Bio)>(),
                .Avatars = ConvertPQXXArrayToVector(row[EColumnIndexes::Avatars]),
            };
            return userData;
        } catch (const std::exception& e) {
            LOG_ERROR << "Canot read user data from table " << TableNames.UsersTable << ". " << e.what();
            return std::nullopt;
        }
    }

    std::optional<bool> TPostgreSQLAdapter::IsUserRegistred(TUserId userId) {
        pqxx::work work(Connection);
        try {
            std::stringstream selectCommand;
            selectCommand << "SELECT EXISTS(SELECT 1 FROM " << TableNames.UsersTable << " WHERE id = " << userId << ");";
            const auto res = work.exec(selectCommand.str());

            if (res.size() != 1 || res[0].size() != 1) {
                LOG_ERROR << "Unknown error while chcking existance of user id=" << userId << " in table " << TableNames.UsersTable;
                return std::nullopt;
            }

            return res[0][0].as<bool>();
        } catch (const std::exception& e) {
            LOG_ERROR << "Canot read user data from table " << TableNames.UsersTable << ". " << e.what();
            return std::nullopt;
        }
    }

    std::optional<TPostgreSQLAdapterPtr> MakePostgeSQLAdapter(
        const std::string& host,
        const std::string& port, 
        const std::string& dbName,
        const std::string& user,
        const std::string& password,
        const TTableNames& tableNames
    ) {
        std::stringstream coonectionOptions;
        coonectionOptions << "host=" << host << " port=" << port << " dbname=" << dbName << " user=" << user << " password=" << password;
        try {
            return std::make_unique<TPostgreSQLAdapter>(coonectionOptions.str(), tableNames);
        } catch (const std::exception &e) {
            LOG_ERROR << e.what();
            return std::nullopt;
        }
    }
}
