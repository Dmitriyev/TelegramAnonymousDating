# MDS binary

Directory contains source code of media data storage

## Structue
### aws_adapter
Class ```TAdapter``` performs data exchange with amazon object storage. Class has two methods:
1. ```LoadImage```. Returns binary image data with given id or ```std::nullopt``` on error
2. ```UploadImage``` Returns avatar id upload into storage or ```std::nullopt``` on error

### config
Defines ```TConfig``` structure that contains amazon object storage configuration and credentials. Function ```ParseConfig``` parses json config and fills ```TConfig``` instance. Returns ```std::nullopt``` on error.

### handlers
Defines and implements functions that handle user requests. Validates data passed and realizes logic described [here](../../doc/mds.md)

## External dependencies
1. jsoncpp - json library https://github.com/open-source-parsers/jsoncpp
2. drogon - http framework https://github.com/drogonframework/drogon
3. aws-sdk-cpp - amazon cloud library https://github.com/aws/aws-sdk-cpp

