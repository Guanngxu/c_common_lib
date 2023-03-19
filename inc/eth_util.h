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

// 以太网头部结构体
typedef struct {
    uint32_t len;
} eth_hdr_t;

/*
* TLV 设计（用于防止粘包）
* 固定 4 个字节作为头
* 4 个字节表示数据长度
* 最后跟长度个数据
*/


int32_t tcp_send(int32_t s, uint8_t *buf, uint32_t send_len);

int32_t tcp_recv(int32_t s, uint8_t *buf, int32_t *recv_len);

void tcp_close(int32_t s);

int32_t tcp_server_init(int16_t port);

int32_t tcp_client_init(uint8_t *host, int16_t port);

#endif
