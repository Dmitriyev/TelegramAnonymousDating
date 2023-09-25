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
psql TAD -q -c "CREATE TABLE [IF NOT EXISTS] users (
    id BIGINT PRIMARY KEY NOT NULL,
    username VARCHAR(50) NOT NULL,
    age SMALLINT NOT NULL,
    sex VARCHAR(10) NOT NULL,
    orientation VARCHAR(10) NOT NULL,
    city VARCHAR(50) NOT NULL,
    bio TEXT
);"

```
- Run ```bin/server```

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

