# TCP Market Data Simulator (C++)

Educational C++ project: evolve a blocking TCP echo into a **market data feed simulator** — binary protocol, multi-client `poll()` server, synthetic ticks, heartbeats, and client reconnect/latency stats.

Built for portfolio / interview depth in quant infrastructure and systems programming — not a real exchange feed.

**Scope (locked):** `TICK` + `HEARTBEAT` only. Single-threaded `poll()` + non-blocking sockets. No order flow.

Concept look-up notes: [`theory/index.html`](theory/index.html) · Full roadmap: [`PLAN.md`](PLAN.md)

---

## Current Features (Baseline)

- Blocking TCP server (accept loop; handles one connection at a time per accept)
- Blocking TCP client (connect → send → receive → close)
- Text echo over TCP
- `SO_REUSEADDR`; Ctrl+C / SIGTERM shutdown on the server

## Roadmap (In Scope)

| Phase | Focus |
|-------|--------|
| 1 | Binary protocol + `key=value` config |
| 2 | `SocketGuard` RAII, `TCP_NODELAY`, minimal logging |
| 3 | Non-blocking sockets + `poll()` multi-client broadcast |
| 4 | Synthetic tick generator (random walk, scaled prices) |
| 5 | Heartbeat + client reconnect with exponential backoff |
| 6 | Client latency percentiles; modular layout; README polish |

**Out of scope:** ORDER/ACK, lock-free queues, epoll/kqueue, TLS/FIX, thread pools — see PLAN.

---

## Project Structure

```
├── CMakeLists.txt
├── PLAN.md
├── README.md
├── src/
│   ├── server.cpp    # TCP server (port 8080)
│   └── client.cpp    # TCP client (127.0.0.1:8080)
├── include/          # Shared headers (protocol, RAII, …)
└── theory/           # Concept look-up notes (HTML)
```

## Requirements

- C++11 or later
- POSIX (Linux, macOS, WSL, …)
- g++ / clang++, CMake 3.10+

## Build

```bash
mkdir -p build && cd build
cmake ..
cmake --build .
```

Produces `server` and `client` in `build/`.

## Run (Current Echo Baseline)

**Terminal 1** — server:

```bash
cd build
./server
```

Expected: `Server listening on port 8080 (all interfaces)... (Ctrl+C to stop)`

**Terminal 2** — client:

```bash
cd build
./client
```

Expected (approx.):

```
Successfully connected to 127.0.0.1:8080
Sent: "Hello from client!" (18 bytes)
Received: "Hello from server!" (18 bytes)
Connection closed. Client exiting.
```

The server stays up across clients until Ctrl+C (each accept currently does one request/reply then closes that client).

## Design Decisions (Target)

- **TCP** — reliable ordered byte stream; fine for a learning market-data feed (UDP/multicast is a different project)
- **Fixed-size binary messages** — no text parsing on the hot path; explicit endianness
- **`poll()`** — portable multi-client I/O without Linux-only `epoll`
- **`TCP_NODELAY`** — disable Nagle for small, latency-sensitive messages
- **App-level heartbeat** — detect dead peers beyond what TCP alone surfaces promptly
