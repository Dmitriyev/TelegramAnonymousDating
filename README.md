# TelegramAnonymousDating
## ToDo list
There are some that we didn't have a time to do:
<details>
    
<summary>List</summary>

1. Unit tests
2. Functionality tests
3. Backend refactoring
4. Frontend refactoring
5. Good search ML algorythm
6. Another json C++ library

</details>

## Overview
Telegram mini app for contest. This app is a dating platform. Implements classic matching logic: when user A likes profile of user B, both of them get links to of each others Telegram profiles

## Application architecture
Telegram anonymous dating is scalable ervice with microservice architecture.

There are 3 microservices in app:
1. Server. Implements buisnesslogic of the app. Language: C++. [Description](doc/server.md)
2. Media data storage (mds). Storage of user's avatars. Language: C++. [Description](doc/mds.md)
3. Frontend. Language: javascript + React. [Description](doc/frontend.md)

Also read about [authentification](doc/authentification.md) of users.

App architecture diagram:
![app architecture](/doc/media/arch.png)

## Build & Run

### Frontend
[Build & start](./frontend/tad_app/README.md)

### Installing dependencies
#### Backend (server + mds)

Dependencies list:

```
cmake
build-essential (For debian-based distrs. Also you can install g++ only)
libjsoncpp-dev
uuid-dev
zlib1g-dev
openssl
libssl-dev
libpqxx-dev
libcurl4-openssl-dev
zlib1g-dev
libssl-dev
libhiredis-dev
postgresql
postgresql-contrib
```

Ubuntu 22.04 users can run following script:

```
sudo scripts/ubuntu_22_04_install_system_deps.sh
```

### Server build & run
#### Building

For building server binary run

```
./build_server.sh
```

#### Preparing server env

1. Build script copies config file into ```bin_server``` directory. Before running server process you should copy ```conf_template.json``` file with different name for example ```conf.json``` (otherwise it wil be rewritten after rebuilding binaries). Than fill config section with your Postgresql, Redis and Telegram bot settings. 
<details>
    
<summary>Fields description</summary>

```server_host: string. Host to run server
  server_port: uint. Port to run server
  postgresql_host: string. Host of PostgreSQL installation
  postgresql_port: string. Port of PostgreSQL installation
  postgresql_db: string. PostgreSQL database name
  postgresql_user_table: string. Name of table with user data
  postgresql_userstring. PostgreSQL user
  postgresql_password: string. PostgreSQL password
  debug_enabled: bool. If it setted to true, binary will not validate initData. Use that mode only for debugging
  telegram_token: string. Telegram bot secret token
```
See also [authentification](doc/authentification.md)

</details>

2. Create PostgreSQL tables\
Run postgres shell
```
sudo -u postgres -i
```
Then create table
```
createdb TAD
psql TAD -q -c "CREATE TABLE IF NOT EXISTS users (
    id BIGINT PRIMARY KEY NOT NULL,
    username VARCHAR(50) NOT NULL,
    age SMALLINT NOT NULL,
    sex SMALLINT NOT NULL,
    orientation SMALLINT NOT NULL,
    city VARCHAR(50) NOT NULL,
    bio TEXT,
    avatars text[] NOT NULL,
    target_sex SMALLINT NOT NULL
);"
```
#### Run

```bin_server/server bin_server/conf.json```


### Mds build & run
#### Building

For building mds binary run

```
./build_mds.sh build_aws    # If you build mds first time. Builds thirdparty aws library
./build_mds.sh              # instead
```
#### Preparing server env
1. Create your own [aws object storage](https://aws.amazon.com/ru/what-is/object-storage/)
2. Build script copies config file into ```bin_mds``` directory. Before running server process you should copy ```conf_template.json``` file with different name for example ```conf.json``` (otherwise it wil be rewritten after rebuilding binaries). Than fill config section with your AWS object storage and Telegram bot settings. 
<details>
    
<summary>Fields description</summary>

```server_host: string. Host to run server
  server_port: uint. Port to run server
  cloud_region: string. AWS storage region
  cloud_endpoint: string. AWS storage endpoint
  cloud_key_id: string. Id of your service account
  cloud_key: string. Secret key of your service account
  cloud_bucket: string. Bucket name where media will store
  debug_enabled: bool. If it setted to true, binary will not validate initData. Use that mode only for debugging
  telegram_token: string. Telegram bot secret token
```
See also [authentification](doc/authentification.md)

</details>

#### Run

```bin_mds/server bin_mds/conf.json```

## Amazon API gateway configuration example
Here we use Yandex.Cloud extension for API gateway:

<details>
    
<summary>Gateway settings</summary>

```
openapi: 3.0.0
info:
  title: Sample API
  version: 1.0.0
servers:
- url: <server url>
paths:
  /api/{path+}:
    x-yc-apigateway-any-method:
      x-yc-apigateway-integration:
        type: http
        url: http://<server IP>/{path}
        query:
          '*': '*'
        headers:
          '*': '*'
      parameters:
      - name: path
        in: path
        required: false
        schema:
          type: string
  /mds/{path+}:
    x-yc-apigateway-any-method:
      x-yc-apigateway-integration:
        type: http
        url: http://<mds IP>/{path}
        query:
          '*': '*'
        headers:
          '*': '*'
      parameters:
      - name: path
        in: path
        required: false
        schema:
          type: string
  /{path+}:
    x-yc-apigateway-any-method:
      x-yc-apigateway-integration:
        type: http
        url: http://<frontend server IP>/{path}
        query:
          '*': '*'
        headers:
          '*': '*'
      parameters:
      - name: path
        in: path
        required: false
        schema:
          type: string

```

</details>
