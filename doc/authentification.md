# Authentification
## Code
Source code kept in [backend/lib/auth_lib](../backend/lib_auth_lib) directory

## How it works

Lib validates initData received from fronend. https://core.telegram.org/bots/webapps#validating-data-received-via-the-mini-app.
InitData passes in ```x-telegram-init-data``` header.

## Settings

There are 2 fields in config files of backend binaries:
```
"debug_enabled": bool. If it setted to true, binary will not validate initData. Use that mode only for debugging
"telegram_token": string. Telegram bot secret token
```


