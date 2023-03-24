#ifndef ETH_UTIL_H
#define ETH_UTIL_H

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>


#define ETH_BUFFER_LEN 3072
#define ETH_SERVER_PORT 6666

// 以太网头部结构体
typedef struct {
    uint32_t len;
} eth_hdr_t;

int32_t tcp_send(int32_t s, char *buf, uint32_t send_len);

int32_t tcp_recv(int32_t s, char *buf, int32_t *recv_len);

int32_t tcp_server_init(int16_t port);

int32_t tcp_client_init(char *host, int16_t port);

#endif
