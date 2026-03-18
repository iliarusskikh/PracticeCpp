# Plan: TCP → Quant-Style Market Data System

A phased roadmap to evolve the simple TCP echo server/client into a DIY project: a low-latency market data simulator with quant-trading infrastructure patterns.

**Purpose:** Reference document to reflect on, update, and track progress. Use checkboxes to mark completion.

---

## Project Goals

- [ ] Demonstrate low-level network programming (Berkeley sockets)
- [ ] Implement a binary protocol (industry-standard approach)
- [ ] Build a market data simulator (tick generator)
- [ ] Apply low-latency techniques used in trading systems

---

## Current State (Baseline)

- [x] Blocking TCP server (single client)
- [x] Blocking TCP client
- [x] Text-based echo (send/receive strings)
- [x] SO_REUSEADDR on server
- [ ] Configuration externalized
- [ ] Binary protocol
- [ ] Multiple clients
- [ ] Reconnection logic

---

## Phase 1: Foundation — Protocol & Configuration

**Goal:** Replace ad-hoc text with structured data and external config.

### 1.1 Binary Protocol

| Step | Description | Status |
|------|-------------|--------|
| 1.1.1 | Define message types (enum: TICK, ORDER, ACK, HEARTBEAT) | [ ] |
| 1.1.2 | Create fixed-size structs for each message type | [ ] |
| 1.1.3 | Handle endianness (htons, htonl, ntohs, ntohl) | [ ] |
| 1.1.4 | Implement serialization/deserialization helpers | [ ] |
| 1.1.5 | Replace text send/recv with binary send/recv | [ ] |

**Concepts:**
- Fixed-size vs length-prefixed messages
- Network byte order (big-endian)
- Struct packing (`#pragma pack`), alignment
- Partial reads: loop until full message received

**Example struct:**
```cpp
#pragma pack(push, 1)
struct TickMsg {
    uint8_t  msg_type;   // 0x01 = TICK
    uint32_t symbol_id;
    int64_t  price;      // scaled (e.g. cents or fixed-point)
    uint32_t timestamp_ns;
    uint32_t volume;
};
#pragma pack(pop)
```

### 1.2 Configuration

| Step | Description | Status |
|------|-------------|--------|
| 1.2.1 | Add config file (JSON or simple key=value) | [ ] |
| 1.2.2 | Load IP, port, symbols from config | [ ] |
| 1.2.3 | Support env vars or CLI overrides | [ ] |

**Concepts:**
- Separation of config from code
- Config validation

### 1.3 Logging

| Step | Description | Status |
|------|-------------|--------|
| 1.3.1 | Add timestamps to log output | [ ] |
| 1.3.2 | Log levels (INFO, WARN, ERROR) | [ ] |
| 1.3.3 | Optional: spdlog or similar (or keep minimal) | [ ] |

---

## Phase 2: Connection Reliability

**Goal:** Robust connections with reconnection and health checks.

### 2.1 Heartbeat / Keepalive

| Step | Description | Status |
|------|-------------|--------|
| 2.1.1 | Define HEARTBEAT message type | [ ] |
| 2.1.2 | Server sends periodic heartbeat (e.g. every 1s) | [ ] |
| 2.1.3 | Client expects heartbeat; detect dead connection on timeout | [ ] |
| 2.1.4 | Client can send heartbeat back (optional) | [ ] |

**Concepts:**
- Idle connection detection
- TCP keepalive vs application-level heartbeat

### 2.2 Reconnection Logic

| Step | Description | Status |
|------|-------------|--------|
| 2.2.1 | Client: retry connect with exponential backoff | [ ] |
| 2.2.2 | Max retries / timeout before giving up | [ ] |
| 2.2.3 | Graceful handling of server restart | [ ] |

**Concepts:**
- Exponential backoff
- Connection state machine (disconnected, connecting, connected)

### 2.3 Socket Options (Low-Latency)

| Step | Description | Status |
|------|-------------|--------|
| 2.3.1 | TCP_NODELAY on both client and server | [ ] |
| 2.3.2 | SO_REUSEADDR (server) — already done | [x] |
| 2.3.3 | Optional: SO_RCVBUF / SO_SNDBUF tuning | [ ] |

**Concepts:**
- Nagle's algorithm and why to disable it
- Socket buffer sizing

---

## Phase 3: Multi-Connection & I/O Multiplexing

**Goal:** Server handles multiple clients; non-blocking or multiplexed I/O.

### 3.1 Multiple Clients (Blocking Loop)

| Step | Description | Status |
|------|-------------|--------|
| 3.1.1 | Loop around accept() to handle multiple clients sequentially | [ ] |
| 3.1.2 | Store client fds; broadcast or unicast ticks | [ ] |

### 3.2 I/O Multiplexing

| Step | Description | Status |
|------|-------------|--------|
| 3.2.1 | Use select() or poll() for multiple fds | [ ] |
| 3.2.2 | Non-blocking sockets (fcntl O_NONBLOCK) | [ ] |
| 3.2.3 | Handle EAGAIN/EWOULDBLOCK in read/write | [ ] |
| 3.2.4 | Optional: epoll (Linux) or kqueue (macOS) | [ ] |

**Concepts:**
- Blocking vs non-blocking I/O
- select() vs poll() vs epoll
- Edge-triggered vs level-triggered

### 3.3 Threading (Alternative)

| Step | Description | Status |
|------|-------------|--------|
| 3.3.1 | One thread per client (simple but not scalable) | [ ] |
| 3.3.2 | Thread pool for handling clients | [ ] |

---

## Phase 4: Market Data Simulator

**Goal:** Server generates synthetic market data; client consumes it.

### 4.1 Tick Generator

| Step | Description | Status |
|------|-------------|--------|
| 4.1.1 | Generate synthetic ticks (price, volume, timestamp) | [ ] |
| 4.1.2 | Configurable symbols and tick rate | [ ] |
| 4.1.3 | Simple random walk or sine-based price model | [ ] |
| 4.1.4 | Optional: order book snapshot (bid/ask) | [ ] |

**Concepts:**
- Tick data structure
- Fixed-point or scaled price representation
- Nanosecond timestamps

### 4.2 Client Consumer

| Step | Description | Status |
|------|-------------|--------|
| 4.2.1 | Parse binary ticks from server | [ ] |
| 4.2.2 | Display or log ticks (e.g. last N) | [ ] |
| 4.2.3 | Optional: simple stats (latency, tick rate) | [ ] |

### 4.3 Order Flow (Optional Extension)

| Step | Description | Status |
|------|-------------|--------|
| 4.3.1 | Client sends ORDER message | [ ] |
| 4.3.2 | Server responds with ACK | [ ] |
| 4.3.3 | Simple order state (New, Ack, Fill) | [ ] |

---

## Phase 5: Low Latency & Performance

**Goal:** Apply techniques used in HFT / quant systems.

### 5.1 Memory & Allocation

| Step | Description | Status |
|------|-------------|--------|
| 5.1.1 | Avoid heap allocation in hot path | [ ] |
| 5.1.2 | Pre-allocated buffers, object pools | [ ] |
| 5.1.3 | Lock-free ring buffer for producer/consumer (see nw_spsc_ring.hpp) | [ ] |

**Concepts:**
- Cache-friendly data layout
- Lock-free data structures
- Memory pools

### 5.2 Latency Measurement

| Step | Description | Status |
|------|-------------|--------|
| 5.2.1 | Measure round-trip or one-way latency | [ ] |
| 5.2.2 | Use high_resolution_clock or rdtsc | [ ] |
| 5.2.3 | Percentiles (p50, p99, p99.9) | [ ] |

**Concepts:**
- Latency histograms
- Clock sources (TSC, HPET)

### 5.3 Build & Runtime

| Step | Description | Status |
|------|-------------|--------|
| 5.3.1 | Release build with -O2/-O3, -march=native | [ ] |
| 5.3.2 | Optional: CPU pinning (pthread_setaffinity) | [ ] |
| 5.3.3 | Optional: huge pages | [ ] |

---

## Phase 6: Polish & Portfolio Readiness

**Goal:** Make the project presentable and resume-worthy.

### 6.1 Code Quality

| Step | Description | Status |
|------|-------------|--------|
| 6.1.1 | Modularize: separate protocol, config, network layers | [ ] |
| 6.1.2 | Add unit tests (e.g. protocol serialization) | [ ] |
| 6.1.3 | README with architecture diagram, usage, design decisions | [ ] |
| 6.1.4 | Comments for non-obvious logic | [ ] |

### 6.2 Documentation

| Step | Description | Status |
|------|-------------|--------|
| 6.2.1 | Protocol specification (message formats) | [ ] |
| 6.2.2 | Build and run instructions | [ ] |
| 6.2.3 | Design doc: why binary protocol, why TCP, trade-offs | [ ] |

### 6.3 Optional Extensions

| Step | Description | Status |
|------|-------------|--------|
| 6.3.1 | TLS (OpenSSL) for encrypted connections | [ ] |
| 6.3.2 | FIX protocol (or simplified subset) | [ ] |
| 6.3.3 | Docker / containerization | [ ] |
| 6.3.4 | Metrics export (Prometheus-style) | [ ] |

---

## Concepts Reference (Learning Checklist)

- [ ] Berkeley sockets lifecycle (socket, bind, listen, accept, connect)
- [ ] TCP vs UDP; when to use each
- [ ] Blocking vs non-blocking I/O
- [ ] select / poll / epoll
- [ ] Network byte order (endianness)
- [ ] Binary protocol design (fixed vs variable length)
- [ ] Nagle's algorithm, TCP_NODELAY
- [ ] SO_REUSEADDR, TIME_WAIT
- [ ] Heartbeat, reconnection, backoff
- [ ] Lock-free queues (SPSC)
- [ ] Latency measurement and percentiles

---

- **"Low-latency TCP market data simulator"** — C++ server/client with binary protocol, multi-client support, heartbeat, reconnection
- **"Binary protocol design"** — Fixed-size messages, endianness, serialization
- **"I/O multiplexing"** — select/poll/epoll for handling multiple connections
- **"Quant infrastructure patterns"** — Tick data, config-driven, latency-aware design

---

*Update this document as you progress. Mark items [x] when done, add notes, adjust phases if needed.*
