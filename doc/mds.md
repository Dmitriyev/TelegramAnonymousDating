# Server decription
## Code
Source code kept in [backend/server](../backend/mds) directory

## Architecture
Storage works over [amazon object storage](https://aws.amazon.com/ru/s3/). Mds is just a proxy server. It [authorize user](./authentification.md) and checks data correctness

## Handlers

### /upload?tg_id={user-id}&format={format}

Uploads image into storage. Implements POST method with binary image data in body.

**Parametrs:**
- tg_id: uint. User's telegram ID
- format: string. Image extension. Supported formats: gif, png, jpg, jpeg

**Return value:**
```
{
  "avatar_path": <avatar_id>
}
```

**Error codes:**
* 400 Reasons: empty request body, not allowed format of image;
* 500 Error writing data into object storage.

### /avatar?id={id}

Return image with passed id. Implements GET method

**Error codes:**
* 500 Error loading file from storage
