# Server decription
## Code
Source code kept in [backend/server](../backend/mds) directory

## Handlers

### /upload?user_id={user-id}&format={format}&md5={md5}

Uploads image into storage. Implements POST method with binary image data in body.

**Parametrs:**
- id: uint. User's telegram ID
- format: string. Image extension. Supported formats: gif, png, jpg, jpeg
- md5: string. File md5 checksum

**Return value:**
```
{
  "avatar_path": <avatar_id>
}
```

**Error codes:**
* 400 Reasons: empty request body, not allowed format of image, md5 cecksum mismatch;
* 500 Error writing data into object storage.

### /avatar?id={id}

Return image with passed id. Implements GET method

**Error codes:**
* 500 Error loading file from storage
