# Server config library
Fills ```TServerConfig``` struct that contains information about host and port of runned server

Function ```ExtractServerConfigFromJson``` creates config and return that. Returns ```std::nullopt`` on error


## External dependencies
1. jsoncpp - json library
2. libcrypto - implements hmac_sha256 hash calculation
