# Simple TCP Echo Server & Client (C++)

A minimal, educational TCP server and client implementation using **Berkeley sockets** API (POSIX sockets).  
Ideal for learning low-level network programming, socket lifecycle, connection handling, and debugging in C++.

## Features

- Basic blocking TCP server that accepts one connection, receives a message, and sends a reply
- Simple TCP client that connects, sends a message, and prints the server's response
- Clean error handling and proper resource cleanup
- Demonstrates classic socket workflow: socket → bind → listen → accept (server) / socket → connect (client)

## Files
├── server.cpp      # TCP server that listens on port 8080
├── client.cpp      # TCP client that connects to 127.0.0.1:8080
└── README.md       # This file

## Requirements
- C++11 or later
- POSIX-compatible system (Linux, macOS, WSL, etc.)
- Compiler: g++ / clang++
- Windows users: use Winsock instead (requires minor changes: WSAStartup, closesocket, etc.)

## Build

### Compile server
g++ -o server server.cpp -std=c++11

### Compile client
g++ -o client client.cpp -std=c++11
Or one-liner:
Bash
g++ -o server server.cpp -std=c++11 && g++ -o client client.cpp -std=c++11

Usage
Start the server (in one terminal):

./server
Expected output:
Server listening on port 8080...

Run the client (in another terminal):
./client
Expected client output:
Connected to server
Message sent: Hello from client!
Reply from server: Hello from server!

Server will print:
Client connected
Message from client: Hello from client!

The server exits after handling one connection (single-shot example).
Restart ./server to accept another connection.


## Customization / Extensions
Common modifications for learning or real use:
Change port: Edit PORT = 8080 in both files
Multiple clients: Add a loop around accept() or use threads / select() / epoll
Non-blocking I/O: Use fcntl(fd, F_SETFL, O_NONBLOCK) + select()/poll()/epoll
Low-latency tweaks:C++int flag = 1;
setsockopt(sock, IPPROTO_TCP, TCP_NODELAY, &flag, sizeof(flag));  // disable Nagle
Reuse port quickly (already included in server):C++setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
Continuous chat: Replace single send/recv with a read-write loop
