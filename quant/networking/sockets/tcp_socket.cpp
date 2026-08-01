#include <netinet/tcp.h>
#include <sys/socket.h>

int setup_low_latency_socket(int fd) {
    int one = 1;

    // Disable Nagle's algorithm — send packets immediately
    // Critical in trading: don't buffer small messages
    setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &one, sizeof(one));

    // Increase socket buffer sizes
    int bufsize = 1 << 20; // 1MB
    setsockopt(fd, SOL_SOCKET, SO_SNDBUF, &bufsize, sizeof(bufsize));
    setsockopt(fd, SOL_SOCKET, SO_RCVBUF, &bufsize, sizeof(bufsize));

    return 0;
}
