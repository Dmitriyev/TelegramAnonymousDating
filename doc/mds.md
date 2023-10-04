# Server decription
## Code
Source code kept in [backend/server](../backend/mds) directory

## Handlers

### /upload?user_id={user-id}&format={format}&md5={md5}

Uploads image into storage. Implements POST method with json body.\
Curl exmaple:

Parametrs:
- id: uint. User's telegram ID
- format: string. Image extension. Supported formats: gif, png, jpg, jpeg
- md5: file md5 checksum

Return value:
```
{
  "avatar_path": <avatar_id>
}
```

### /avatar?id={id}

Return image with passed id. Implements GET method
