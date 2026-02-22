//htons()
//Host To Network Short
//Converts a 16-bit integer from host byte order to network byte order (which is always big-endian)
//
//htonl()
//Host To Network Long
//Converts a 32-bit integer from host byte order to network byte order (big-endian)
//
//ntohs()
//Network To Host Short
//Converts a 16-bit integer from network byte order (big-endian) to host byte order
//
//ntohl()
//Network To Host Long
//Converts a 32-bit integer from network byte order (big-endian) to host byte order

#include <iostream>
#include <cstdint>        // uint16_t, uint32_t
#include <arpa/inet.h>    // ntohs, ntohl, htons, htonl

int main()
{
    // ──────────────────────────────────────────────
    // Sending data
    // ──────────────────────────────────────────────
    uint16_t port_host = 8080; // 0x1F90 in memory: [90, 1F]
    uint16_t port_network = htons(port_host);   // make sure it's big-endian
    // becomes [1F, 90] = 0x1F90 in network order

    uint32_t magic_host = 0xDEADBEEF;
    uint32_t magic_network = htonl(magic_host);

    std::cout << "port host: " << port_host << "\n";
    std::cout << "port network: 0x" << std::hex << port_network << "\n";

    // ──────────────────────────────────────────────
    // Receiving data
    // ──────────────────────────────────────────────
    uint32_t received = 0xEFBEADDE;             // suppose this came from network
    uint32_t received_host = ntohl(received);   // convert back to host order little endian

    std::cout << "received (network order): 0x" << std::hex << received << "\n";
    std::cout << "received (host order):    0x" << std::hex << received_host << "\n";

    return EXIT_SUCCESS;
}
