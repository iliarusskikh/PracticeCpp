#include <iostream>          // For std::cout, std::cerr
#include <cstring>           // For strlen()
#include <sys/socket.h>      // socket(), connect(), send(), read(), close()
#include <netinet/in.h>      // sockaddr_in, htons()
#include <arpa/inet.h>       // inet_pton() — modern way to convert IP string → binary
#include <unistd.h>          // close(), read()  (on POSIX systems)

#include "timer.hpp"

int main() {
    Timer timer; //creating object - starting the timer

    // ────────────────────────────────────────────────
    //                VARIABLES
    // ────────────────────────────────────────────────
    int sock = -1;                      // Socket file descriptor (will be set by socket())
    struct sockaddr_in serv_addr;       // Structure that holds server's IP + port
    const char* message = "Hello from client!";   // Data we will send
    char buffer[1024] = {0};            // Buffer to receive server's reply (zero-initialized)
    const char* SERVER_IP = "127.0.0.1"; // localhost (loopback address)
    const int PORT = 8080;              // Port the server is listening on

    // ────────────────────────────────────────────────
    // 1. CREATE SOCKET
    // ────────────────────────────────────────────────
    // AF_INET    → IPv4
    // SOCK_STREAM → TCP (reliable, connection-oriented, byte stream)
    // 0          → use default protocol (IPPROTO_TCP)
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Error: Failed to create socket\n";
        return 1;
    }
    // At this point we have a socket file descriptor (like a handle)

    // ────────────────────────────────────────────────
    // 2. PREPARE SERVER ADDRESS STRUCTURE
    // ────────────────────────────────────────────────
    // Clear structure (good practice, though not always strictly needed)
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;           // Must match socket family (IPv4)
    serv_addr.sin_port   = htons(PORT);       // Convert port to network byte order (big-endian)

    // Convert IP string ("127.0.0.1") → 32-bit binary format
    // inet_pton = "presentation to network"
    if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0) {
        std::cerr << "Error: Invalid IP address\n";
        close(sock);
        return 1;
    }

    // ────────────────────────────────────────────────
    // 3. CONNECT TO THE SERVER
    // ────────────────────────────────────────────────
    // Initiates TCP 3-way handshake
    // Blocks until connection succeeds or fails
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Error: Connection failed (server down? wrong port?)\n";
        close(sock);
        return 1;
    }

    std::cout << "Successfully connected to " << SERVER_IP << ":" << PORT << "\n";

    // ────────────────────────────────────────────────
    // 4. SEND DATA
    // ────────────────────────────────────────────────
    // send() may not send everything in one call in general,
    // but here message is tiny → almost always succeeds in one go
    ssize_t bytes_sent = send(sock, message, strlen(message), 0);
    if (bytes_sent < 0) {
        std::cerr << "Error: Send failed\n";
        close(sock);
        return 1;
    }

    std::cout << "Sent: \"" << message << "\" (" << bytes_sent << " bytes)\n";

    // ────────────────────────────────────────────────
    // 5. RECEIVE RESPONSE (simple blocking read)
    // ────────────────────────────────────────────────
    // read() blocks until data arrives or connection closes
    ssize_t bytes_received = read(sock, buffer, sizeof(buffer) - 1);
    if (bytes_received < 0) {
        std::cerr << "Error: Read failed\n";
    } else if (bytes_received == 0) {
        std::cout << "Server closed connection\n";
    } else {
        buffer[bytes_received] = '\0';           // Null-terminate for safe printing
        std::cout << "Received: \"" << buffer << "\" (" << bytes_received << " bytes)\n";
    }

    // ────────────────────────────────────────────────
    // 6. CLEAN UP
    // ────────────────────────────────────────────────
    // Closing socket sends FIN → starts graceful TCP shutdown
    close(sock);

    std::cout << "Connection closed. Client exiting.\n";

    return EXIT_SUCCESS;
}
