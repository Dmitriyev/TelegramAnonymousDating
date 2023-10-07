# Server binary

Directory contains source code of [server](../../doc/server.md)

## Structue
### common
Defines common structers and serialization/deserialization helpers for them
1. ```TUser``` - information about dating's user such as name, age, sex etc

### config
Defines ```TConfig``` structure that contains PostgreSQL and Redis databases configuration and credentials. Function ```ParseConfig``` parses json config and fills ```TConfig``` instance. Returns ```std::nullopt``` on error.

### db_adapter
1. Class ```TPostgreSQLAdapter``` implements read and write operations for Postgresql database with user's data

### handlers
Defines and implements functions that handle user requests. Validates data passed and realizes logic described [here](../../doc/server.md)

## External dependencies
1. jsoncpp - json library https://github.com/open-source-parsers/jsoncpp
2. drogon - http framework and redis database adapter https://github.com/drogonframework/drogon
3. pqxx - PostgreSQL library https://github.com/jtv/libpqxx
