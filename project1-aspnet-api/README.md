# File Transfer API

ASP.NET Core controller/service application for the file-transfer wireframe.
It receives files and chunks from C++, can send files to the C++ HTTP server,
and exposes a received-file listing and download API.

## Run

```bash
dotnet run
```

The default storage root is `storage/`. Set `StoragePath` in
`appsettings.json` to change it.

## API

| Method | Endpoint | Purpose |
| --- | --- | --- |
| `GET` | `/api/health` | Health check |
| `POST` | `/api/files/{fileName}/file` | Receive one complete file |
| `POST` | `/api/files/{transferId}/chunks/{chunkNumber}` | Receive a chunk |
| `POST` | `/api/files/{transferId}/rebuild` | Rebuild received chunks |
| `POST` | `/api/streams/{streamId}/data` | Append continuous data |
| `GET` | `/api/files` | List received files |
| `GET` | `/api/files/{fileName}` | Download a received file |

Files smaller than 100 MB are transferred as one request. Larger files use
1 MB chunks. The implementation intentionally does not include authentication,
checksums, retries, encryption, or missing-chunk detection yet.

## Example

```bash
curl -X POST -H "Content-Type: application/octet-stream" --data-binary @example.bin \
  http://localhost:5000/api/files/example.bin/file
curl http://localhost:5000/api/files
curl -OJ http://localhost:5000/api/files/example.bin
```
