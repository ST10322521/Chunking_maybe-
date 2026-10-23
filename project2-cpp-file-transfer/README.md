# C++ File Transfer App

C++20 file-transfer client and HTTP server. libcurl is used for C++ to C#
requests. The inbound HTTP server is a small POSIX socket implementation, so
no separate `cpp-httplib` package is required.

## Build

Install a libcurl development package, then run:

```bash
cmake -S . -B build
cmake --build build
```

## Commands

```bash
# Start the C++ HTTP server for C# -> C++ transfers.
./build/file_transfer_app server [port]

# Send a file to the C# API. Files >= 100 MB use 1 MB chunks.
./build/file_transfer_app send-file <file> <transferId> [apiUrl]

# Rebuild chunks received by the C++ server.
./build/file_transfer_app rebuild <transferId> <output>

# Append continuous text data to the C# stream endpoint.
./build/file_transfer_app send-stream <streamId> <text> [apiUrl]
```

The default C# API URL is `http://localhost:5000`. Received C++ files and
chunks are stored under `storage/files/`.
