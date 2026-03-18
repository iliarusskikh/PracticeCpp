//g++ -o server server.cpp -std=c++11
//Server: create → bind → listen → accept → receive → send → close

#include <iostream>          // std::cout, std::cerr
#include <cstring>           // memset, strlen
#include <sys/socket.h>      // socket(), bind(), listen(), accept(), send(), read(), setsockopt()
#include <netinet/in.h>      // sockaddr_in, htons(), INADDR_ANY
#include <unistd.h>          // close(), read()

int main() {
    // ────────────────────────────────────────────────
    //                VARIABLES
    // ────────────────────────────────────────────────
    int server_fd = -1;                  // Listening socket file descriptor
    int new_socket = -1;                 // Connected socket (for one client in this simple version)
    struct sockaddr_in address;          // Structure for our server's address
    int addrlen = sizeof(address);       // Will be updated by accept()
    const int PORT = 8080;
    char buffer[1024] = {0};             // Buffer to store incoming client message

    // ────────────────────────────────────────────────
    // 1. CREATE LISTENING SOCKET
    // ────────────────────────────────────────────────
    // AF_INET    → IPv4
    // SOCK_STREAM → TCP (reliable, connection-oriented)
    // 0          → default protocol (IPPROTO_TCP)
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Error: Socket creation failed\n";
        return 1;
    }

    // ────────────────────────────────────────────────
    // Optional but VERY IMPORTANT: Allow quick port reuse
    // ────────────────────────────────────────────────
    // Prevents "Address already in use" after quick server restart
    // (due to TIME_WAIT state from previous connections)
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Warning: setsockopt(SO_REUSEADDR) failed\n";
        // Not fatal → we can continue
    }

    // ────────────────────────────────────────────────
    // 2. PREPARE SERVER ADDRESS STRUCTURE
    // ────────────────────────────────────────────────
    // Good practice: zero out the structure
    memset(&address, 0, sizeof(address));

    address.sin_family      = AF_INET;              // IPv4
    address.sin_addr.s_addr = INADDR_ANY;           // 0.0.0.0 → accept connections on ALL interfaces
    address.sin_port        = htons(PORT);          // Convert port to network byte order

    // ────────────────────────────────────────────────
    // 3. BIND socket to the address/port
    // ────────────────────────────────────────────────
    // Associates the socket with a concrete IP:port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Error: Bind failed (port in use? permissions?)\n";
        close(server_fd);
        return 1;
    }

    // ────────────────────────────────────────────────
    // 4. LISTEN for incoming connections
    // ────────────────────────────────────────────────
    // backlog = 3 → queue up to 3 pending connections before refusing new ones
    // Modern systems often ignore exact value and use larger internal queue
    if (listen(server_fd, 3) < 0) {
        std::cerr << "Error: Listen failed\n";
        close(server_fd);
        return 1;
    }

    std::cout << "Server listening on port " << PORT << " (all interfaces)...\n";

    // ────────────────────────────────────────────────
    // 5. ACCEPT a client connection (blocking call)
    // ────────────────────────────────────────────────
    // Blocks until a client connects
    // Creates a NEW socket (new_socket) for THIS client
    // server_fd remains listening for more clients
    new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) {
        std::cerr << "Error: Accept failed\n";
        close(server_fd);
        return 1;
    }

    std::cout << "Client connected\n";

    // ────────────────────────────────────────────────
    // 6. READ data from the connected client
    // ────────────────────────────────────────────────
    // read() blocks until data arrives or connection closes
    int valread = read(new_socket, buffer, sizeof(buffer) - 1);
    if (valread < 0) {
        std::cerr << "Error: Read failed\n";
    } else if (valread == 0) {
        std::cout << "Client closed connection\n";
    } else {
        buffer[valread] = '\0';                     // Null-terminate for safe printing
        std::cout << "Message from client: \"" << buffer << "\" (" << valread << " bytes)\n";
    }

    // ────────────────────────────────────────────────
    // 7. SEND reply back to client (echo / greeting)
    // ────────────────────────────────────────────────
    const char* reply = "Hello from server!";
    ssize_t bytes_sent = send(new_socket, reply, strlen(reply), 0);
    if (bytes_sent < 0) {
        std::cerr << "Warning: Send failed\n";
    } else {
        std::cout << "Replied: \"" << reply << "\"\n";
    }

    // ────────────────────────────────────────────────
    // 8. CLEAN UP
    // ────────────────────────────────────────────────
    // Close the client connection first
    close(new_socket);
    // Then close the listening socket
    close(server_fd);

    std::cout << "Server shutting down.\n";

    return 0;
}
