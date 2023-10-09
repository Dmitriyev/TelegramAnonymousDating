# Server decription
## Code
Source code kept in [backend/server](../backend/server) directory

## Architecture
User accounts data stores in [PostgreSQL database](https://www.postgresql.org/).
Information about user likes and dislikes stores in [Redis database](https://redis.io/)

## Handlers

### /register

Calls once for reister new user. Implements POST method with json body.\
**Curl exmaple:**

```
curl -H "Content-Type: application/json" -d '{"name": "Alex", <...>}' -X POST http://127.0.0.1:8848/register
```

**Json body fields:**
- id: uint. User's telegram ID
- name: string
- age: uint
- sex: string. Possible values: man, woman
- orientation: string. Possible values: straight, bi, gay
- city: string
- bio: string
- avatars: list of strings. Ids of user's avatars at [mds](./mds.md)

**Error codes:**
* 400 Reasons: empty request body, incorrect json passed
* 500 Error writing database

### /edit\_account

Edits user account. Parameter are same as in the [/register](#-/register) header. Implements POST method with json body.\

**Error codes:**
* 400 Reasons: empty request body, incorrect json passed
* 500 Error writing database

### /account\_info\?user\_id\=\<id\>

Returns account info. Implements GET method. Returns json with keys described in [/register](#-/register) method

**Error codes:**
* 400 Not-numeric user_id passed
* 500 Error reading database

### /start\?user\_id\=\<id\>

Checks is user registred in app. Returns json with following format:\
```
{
    "user_registred": <true/false>
}
```

**Error codes:**
* 400 Not-numeric user_id passed
* 500 Error reading database
