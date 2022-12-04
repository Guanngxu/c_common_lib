#include "eth_util.h"

int main(uint32_t argc, char **argv)
{
    int32_t socket_fd = tcp_server_init(6666);
    uint8_t send_data[16];
    memset(send_data, 0, 16);
    while(1) {
	    tcp_send(socket_fd, send_data, 16);
        int32_t i;
        for(i = 0; i < 16; i++) {
            send_data[i] += 1;
        }
        sleep(5);
    }
}