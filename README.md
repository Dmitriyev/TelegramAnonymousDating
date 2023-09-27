# TelegramAnonymousDating
Telegram mini app for contest

# Building server
## Installing dependencies
Dependencies list:

```
jsoncpp
zlib
openssl
libssl
```

Ubuntu 22.04 users can use following command once:

```
sudo scripts/ubuntu_22_04_install_system_deps.sh
```

## Build

```
./build.sh
```
Build script copies config file into bin directory. Before running server process you should copy ```conf\_template.json``` file with different name for example ```conf.json``` (otherwise it wil be rewritten after rebuilding binaries). Than fill ```postgresql_user``` and ```postgresql_password``` with correct credentials. 

# Starting server
- Start Postges database service ```sudo scripts/prepare_server_env.sh```
- Create tables if needed\
Run postgres shell
```
sudo -u postgres -i
```
Then create tables
```
createdb TAD
psql TAD -q -c "CREATE TABLE IF NOT EXISTS users (
    id BIGINT PRIMARY KEY NOT NULL,
    username VARCHAR(50) NOT NULL,
    age SMALLINT NOT NULL,
    sex SMALLINT NOT NULL,
    orientation SMALLINT NOT NULL,
    city VARCHAR(50) NOT NULL,
    bio TEXT
);"
```
- Run ```bin/server conf.json```

# Server decription

## Handlers

### /register

Calls once for reister new user. Implements POST method with json body.\
Curl exmaple:

```
curl -H "Content-Type: application/json" -d '{"name": "Alex", <...>}' -X POST http://127.0.0.1:8848/register
```

Json fields:
- id: uint. User's telegram ID
- name: string
- age: uint
- sex: string. Possible values: man, woman
- orientation: string. Possible values: straight, bi, gay
- city: string
- bio: string

### /edit\_account

Edits user account. Parameter are same as in the [/register](#-/register) header. Implements POST method with json body.\

### account\_info\?user\_id\=

Returns account info. Implements GET method. Returns json with keys described in [/register](#-/register) method
