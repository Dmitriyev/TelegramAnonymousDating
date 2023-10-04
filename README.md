# TelegramAnonymousDating
## Overview
Telegram mini app for contest. This app is a dating platform. Implements classic matching logic: when user A likes profile of user B, both of them get links to of each others Telegram profiles

## Application architecture
There are 3 microservices in app:
1. Server. Implements buisnesslogic of the app. Language: C++ 
2. Media data storage (mds). Storage of user's avatars. Language: C++
3. Frontend. Language: javascript + React

App architecture diagram:
![app architecture](/doc/media/arch.png)

## Build & Run
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
postgresql
postgresql-contrib
```

Ubuntu 22.04 users can run following script:

```
sudo scripts/ubuntu_22_04_install_system_deps.sh
```

#### Frontend
[ToDo avraam]

### Server build & run
#### Building

For building server binary run

```
./build_server.sh
```

#### Preparing server env

1. Build script copies config file into ```bin_server``` directory. Before running server process you should copy ```conf\_template.json``` file with different name for example ```conf.json``` (otherwise it wil be rewritten after rebuilding binaries). Than fill config section with your Postgresql, Redis and Telegram bot settings. 
<details>
    
<summary>Fields description</summary>

```server_host - host to run server
  server_port - port to run server
  postgresql_host - host of PostgreSQL installation
  postgresql_port - port of PostgreSQL installation
  postgresql_db - database name
  postgresql_user_table - name of table with user data
  postgresql_user - PostgreSQL user
  postgresql_password - PostgreSQL password
```

</details>

2. Create PostgreSQL tables 
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
    bio TEXT
);"
```
#### Run

```bin_server/server bin_server/conf.json```


### Mds build & run
#### Building

For building mds binary run

```
./build_mds.sh
```
#### Preparing server env
1. Create your own [aws object storage](https://aws.amazon.com/ru/what-is/object-storage/)
2. Build script copies config file into ```bin_mds``` directory. Before running server process you should copy ```conf\_template.json``` file with different name for example ```conf.json``` (otherwise it wil be rewritten after rebuilding binaries). Than fill config section with your AWS object storage and Telegram bot settings. 
<details>
    
<summary>Fields description</summary>

```server_host - host to run server
  server_port - port to run server
  cloud_region - AWS storage region
  cloud_endpoint - AWS storage endpoint
  cloud_key_id - id of your service account
  cloud_key - secret key of your service account
  cloud_bucket - bucket name where media will store
```

</details>

#### Run

```bin_mds/server bin_mds/conf.json```


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

### /account\_info\?user\_id\=\<id\>

Returns account info. Implements GET method. Returns json with keys described in [/register](#-/register) method

### /start\?user\_id\=\<id\>

Checks is user registred in app. Returns json with following format:\
```
{
    "user_registred": <true/false>
}
```
