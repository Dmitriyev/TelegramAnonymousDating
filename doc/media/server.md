# Server decription
## Code
Source code kept in [backend/server](https://github.com/Dmitriyev/TelegramAnonymousDating/tree/main/backend/server) directory

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
