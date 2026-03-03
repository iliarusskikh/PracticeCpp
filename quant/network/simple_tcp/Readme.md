# Simple TCP Echo Server & Client (C++)

A minimal, educational TCP server and client implementation using **Berkeley sockets** API (POSIX sockets).  
Ideal for learning low-level network programming, socket lifecycle, connection handling, and debugging in C++.

*Future direction: extend into a server/client market data simulator for quant portfolio work.*

## Features

- Basic blocking TCP server that accepts one connection, receives a message, and sends a reply
- Simple TCP client that connects, sends a message, and prints the server's response
- Clean error handling and proper resource cleanup
- Demonstrates classic socket workflow: socket → bind → listen → accept (server) / socket → connect (client)

## Project Structure

```
├── CMakeLists.txt    # CMake build configuration
├── src/
│   ├── server.cpp    # TCP server (listens on port 8080)
│   └── client.cpp    # TCP client (connects to 127.0.0.1:8080)
├── include/          # Future shared headers (protocol, market data types)
└── README.md
```

## Requirements

- C++11 or later
- POSIX-compatible system (Linux, macOS, WSL, etc.)
- Compiler: g++ / clang++
- CMake 3.10+
- Windows users: use Winsock instead (requires minor changes: WSAStartup, closesocket, etc.)

## Build

```bash
mkdir build && cd build
cmake ..
cmake --build .
```

This produces the `server` and `client` executables in the `build/` directory.

## Run

**Terminal 1** – start the server:

```bash
cd build
./server
```

Expected output: `Server listening on port 8080 (all interfaces)...`

**Terminal 2** – run the client:

```bash
cd build
./client
```

Expected client output:

```
Successfully connected to 127.0.0.1:8080
Sent: "Hello from client!" (18 bytes)
Received: "Hello from server!" (18 bytes)
Connection closed. Client exiting.
```

The server exits after handling one connection. Restart `./server` to accept another connection.

## Customization / Extensions

Common modifications for learning or real use:

- **Change port:** Edit `PORT = 8080` in both `server.cpp` and `client.cpp`
- **Multiple clients:** Add a loop around `accept()` or use threads / `select()` / `epoll`
- **Non-blocking I/O:** Use `fcntl(fd, F_SETFL, O_NONBLOCK)` + `select()`/`poll()`/`epoll`
- **Low-latency tweaks:**
  ```cpp
  int flag = 1;
  setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));  // disable Nagle
  ```
- **Reuse port quickly** (already included in server):
  ```cpp
  setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  ```
- **Continuous chat:** Replace single send/recv with a read-write loop
