#include "eth_util.h"

int main(uint32_t argc, char **argv)
{
    int32_t socket_fd = tcp_client_init("192.168.0.3", 6666);
    uint8_t recv_buf[32];
    while(1) {
        int len = 0;
	    tcp_recv(socket_fd, recv_buf, &len);
    }
}