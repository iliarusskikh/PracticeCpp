# Plan: TCP Market Data Simulator

Phased roadmap from the blocking TCP echo baseline to a CV-ready, low-latency-style market data feed simulator.

**Scope lock:** market data only (`TICK` + `HEARTBEAT`). Single-threaded `poll()` + non-blocking sockets. No order flow.

**Purpose:** Track progress with checkboxes. Theory notes live in [`theory/`](theory/index.html).

---

## Project Goals

- [ ] Demonstrate Berkeley sockets (TCP server/client lifecycle)
- [ ] Implement a fixed-size binary protocol with endianness handling
- [ ] Build a synthetic tick generator (market data simulator)
- [ ] Serve multiple clients via `poll()` in one thread
- [ ] Apply a few latency-oriented patterns: `TCP_NODELAY`, heartbeats, reconnect, latency percentiles

**CV one-liner:** C++ TCP market data feed simulator — binary protocol, multi-client `poll()` server, heartbeats/reconnect, synthetic ticks, client latency stats.

---

## Current State (Baseline)

- [x] Blocking TCP server (accept loop; one client at a time per accept)
- [x] Blocking TCP client
- [x] Text-based echo (send/receive strings)
- [x] `SO_REUSEADDR` on server
- [x] Signal-aware shutdown (`SIGINT` / `SIGTERM`)
- [ ] Binary protocol
- [ ] Configuration externalized
- [ ] RAII socket ownership
- [ ] Multiple concurrent clients (`poll`)
- [ ] Heartbeat / reconnection

---

## Phase 0: Baseline — Done

Blocking echo server/client. See [README.md](README.md) for build/run.

---

## Phase 1: Binary Protocol & Configuration

**Goal:** Replace ad-hoc text with structured binary messages and external config.

### 1.1 Binary Protocol

| Step | Description | Status |
|------|-------------|--------|
| 1.1.1 | Define `MsgType` enum: `TICK`, `HEARTBEAT` | [ ] |
| 1.1.2 | Fixed-size packed structs for each type | [ ] |
| 1.1.3 | Endianness helpers (`htons` / `htonl` / `ntoh*`, and 64-bit if needed) | [ ] |
| 1.1.4 | Serialize / deserialize helpers | [ ] |
| 1.1.5 | Replace text send/recv with binary; loop until full message | [ ] |

**Concepts:** fixed-size messages, network byte order, `#pragma pack`, partial reads.  
**Theory:** [Binary Protocol](theory/Theory_Binary_Protocol.html)

**Sketch:**
```cpp
#pragma pack(push, 1)
struct TickMsg {
    uint8_t  msg_type;      // TICK
    uint32_t symbol_id;
    int64_t  price;         // scaled integer (e.g. micros)
    uint64_t timestamp_ns;  // or steady-clock ticks
    uint32_t volume;
};
struct HeartbeatMsg {
    uint8_t  msg_type;      // HEARTBEAT
    uint64_t timestamp_ns;
};
#pragma pack(pop)
```

### 1.2 Configuration

| Step | Description | Status |
|------|-------------|--------|
| 1.2.1 | Simple `key=value` config file | [ ] |
| 1.2.2 | Load host, port, symbols, tick rate from config | [ ] |
| 1.2.3 | Validate required keys; sane defaults | [ ] |

---

## Phase 2: RAII, Socket Options, Logging

**Goal:** Safe resource ownership and a couple of latency-relevant socket options.

### 2.1 RAII

| Step | Description | Status |
|------|-------------|--------|
| 2.1.1 | `SocketGuard` (or equivalent) — acquire fd, `close` in destructor | [ ] |
| 2.1.2 | Move-only; delete copy | [ ] |
| 2.1.3 | Use for listen socket, accepted clients, and client connect socket | [ ] |

**Theory:** [RAII](theory/Theory_RAII.html)

### 2.2 Socket Options

| Step | Description | Status |
|------|-------------|--------|
| 2.2.1 | `TCP_NODELAY` on server accepted sockets and client | [ ] |
| 2.2.2 | `SO_REUSEADDR` (server) — already done | [x] |

**Theory:** [Socket Options & Nagle](theory/Theory_Socket_Options_Nagle.html)

### 2.3 Logging

| Step | Description | Status |
|------|-------------|--------|
| 2.3.1 | Timestamps on log lines | [ ] |
| 2.3.2 | Levels: INFO, WARN, ERROR (minimal macros or functions) | [ ] |

Keep logging minimal — no third-party logger.

---

## Phase 3: Multi-Client via `poll()`

**Goal:** One thread serves many clients with non-blocking I/O.

| Step | Description | Status |
|------|-------------|--------|
| 3.1 | Set listen + client sockets `O_NONBLOCK` | [ ] |
| 3.2 | `poll()` over listen fd + client fds | [ ] |
| 3.3 | Accept new clients when listen is readable | [ ] |
| 3.4 | Handle `EAGAIN` / `EWOULDBLOCK` on read/write | [ ] |
| 3.5 | Broadcast ticks (and later heartbeats) to all connected clients | [ ] |
| 3.6 | Drop disconnected clients cleanly | [ ] |

**Theory:** [Non-Blocking & poll](theory/Theory_NonBlocking_Poll.html)

---

## Phase 4: Market Data Simulator

**Goal:** Server generates synthetic ticks; clients consume them.

### 4.1 Tick Generator

| Step | Description | Status |
|------|-------------|--------|
| 4.1.1 | Generate ticks (symbol, scaled price, volume, timestamp) | [ ] |
| 4.1.2 | Configurable symbols and tick rate | [ ] |
| 4.1.3 | Simple random-walk price model | [ ] |

### 4.2 Client Consumer

| Step | Description | Status |
|------|-------------|--------|
| 4.2.1 | Parse binary ticks | [ ] |
| 4.2.2 | Log / display recent ticks | [ ] |

**Theory:** [Market Data Ticks](theory/Theory_Market_Data_Ticks.html)

---

## Phase 5: Heartbeat & Reconnection

**Goal:** Detect dead connections; recover from server restart.

| Step | Description | Status |
|------|-------------|--------|
| 5.1 | Server sends periodic `HEARTBEAT` | [ ] |
| 5.2 | Client tracks last message time; timeout → treat as dead | [ ] |
| 5.3 | Client reconnect with exponential backoff + max retries | [ ] |
| 5.4 | Connection state: disconnected → connecting → connected | [ ] |

**Theory:** [Heartbeat & Reconnect](theory/Theory_Heartbeat_Reconnect.html)

---

## Phase 6: Latency Stats & Portfolio Polish

**Goal:** Presentable, interview-ready project.

| Step | Description | Status |
|------|-------------|--------|
| 6.1 | Client: measure inter-arrival or stamp-based latency; report p50 / p99 | [ ] |
| 6.2 | Modularize: `protocol.hpp`, config, network helpers | [ ] |
| 6.3 | README: architecture, protocol summary, design decisions | [ ] |
| 6.4 | Protocol note (message layouts) in README or short `docs/protocol.md` | [ ] |
| 6.5 | Release build flags (`-O2` / `-O3`) documented | [ ] |

**Theory:** [Latency Measurement](theory/Theory_Latency_Measurement.html)

---

## Out of Scope (deliberate cuts)

These are useful topics for other projects — not this one:

| Cut | Why |
|-----|-----|
| ORDER / ACK, order book | Market-data-only scope |
| Lock-free SPSC rings, object pools | Separate concurrency/HFT deep-dive |
| epoll / kqueue | `poll()` is portable and enough for the story |
| Thread pool / thread-per-client | Single-threaded `poll` is the architecture |
| CPU pinning, huge pages, rdtsc | Overkill for a learning simulator |
| TLS, FIX, Docker, Prometheus | Ops/protocol surface beyond the goal |
| JSON + env/CLI config matrix, spdlog | Keep config and logging minimal |

---

## Concepts Checklist

- [ ] Berkeley sockets lifecycle — [Sockets & TCP](theory/Theory_Sockets_TCP.html)
- [ ] TCP vs UDP; why TCP here
- [ ] Binary protocol, endianness, partial reads
- [ ] Blocking vs non-blocking; `poll`
- [ ] Nagle / `TCP_NODELAY`
- [ ] `SO_REUSEADDR` / TIME_WAIT
- [ ] Heartbeat vs TCP keepalive; backoff
- [ ] Scaled prices; synthetic ticks
- [ ] Latency percentiles
- [ ] RAII for socket fds

---

*Update checkboxes as you go. Implementation starts after reading the theory notes.*
