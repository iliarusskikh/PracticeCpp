#include <bit>
#include <cstdint>
#include <iostream>
#include <cstring>      // memset
#include <arpa/inet.h>  // socket, connect, etc.
#include <unistd.h>     // close
#include <sys/socket.h>

uint32_t to_network(uint32_t v) {
    if constexpr (std::endian::native == std::endian::little) {
        return std::byteswap(v);
    }
    return v;
}

uint32_t to_host(uint32_t v) {
    return to_network(v);
}

int main() {
    // ────────────────────────────────
    // Very simple TCP client
    // ────────────────────────────────
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "socket failed\n";
        return 1;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port   = to_network(8080);           // covnersion
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        std::cerr << "connect failed\n";
        close(sock);
        return 1;
    }

    uint32_t value_to_send = 0xDEADBEEF;
    uint32_t network_value = to_network(value_to_send);

    if (send(sock, &network_value, sizeof(network_value), 0) < 0) {
        std::cerr << "send failed\n";
    } else {
        std::cout << "Sent: 0x" << std::hex << value_to_send << "\n";
    }

    close(sock);
    
    
    
    //applying conversion two times to showcase send/receive endinness pattern
    uint32_t x = 0x12345678;

    uint32_t net  = to_network(x);
    uint32_t back = to_host(net);
    
    
    return EXIT_SUCCESS;
}


/*
 //server side
 
 // ... socket, bind, listen, accept ...

 uint32_t received_net;
 recv(client_sock, &received_net, sizeof(received_net), 0);

 uint32_t received_host = to_host(received_net);  // ← using your function

 std::cout << "Received: 0x" << std::hex << received_host << "\n";
 
 
 */


/*
 Next steps:
 - a complete minimal UDP example
 - a complete minimal TCP echo server/client
 - how to extend to_network/to_host to 64-bit values
 
 */
