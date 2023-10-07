# Authentification library

[Validates](https://core.telegram.org/bots/webapps#validating-data-received-via-the-mini-app) telegram initData passed. 

The main object is ```IAuthorizer``` interface. Defined in [auth.h](./auth.h) header. Method ```IsUserAuthentificated``` validates initData passed into that.

There are two implementations in [auth.cpp](./auth.cpp) file:
1. ```TDummyAuthorizer``` Always returns true. ***Use it only for debuging***
2. ```TAuthorizer``` implements validating logic

Function ```MakeAuthorizer``` constructs one of implementations depends on json config passed. If config has key ```debug_enabled``` and it's value is ```true```, function constructs ```TDummyAuthorizer```. In another case it constructs ```TAuthorizer``` instance

## Dependencies
1. jsoncpp - json library
2. libcrypto - implements hmac_sha256 hash calculation
