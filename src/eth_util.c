#include "../inc/eth_util.h"

int32_t tcp_send(int32_t s, uint8_t *buf, uint32_t send_len) {
	int32_t ret;

	eth_hdr_t eth_hdr = {0};
	// 转换主机字节序为网络字节序
	eth_hdr.len = htonl(send_len);

	// 发送帧头
	ret =  write(s, (uint8_t *)&eth_hdr, sizeof(eth_hdr_t));
	if(ret <= 0) {
		printf("write header err[ret = %d].\n", ret);
		return -1;
	}

	// 发送实际数据
	ret =  write(s, buf, send_len);
	if(ret <= 0) {
		printf("write data err[ret = %d].\n", ret);
		return -1;
	}
	return ret;
}

int32_t tcp_recv(int32_t s, uint8_t *buf, int buf_len, int32_t *recv_len) {
	int32_t ret;
	eth_hdr_t eth_hdr = {0};

	// 读取帧头
	ret =  read(s, (uint8_t *)&eth_hdr, sizeof(eth_hdr_t));
	// 转换网络字节序为主机字节序
	eth_hdr.len = ntohl(eth_hdr.len);
	if(ret < 0) {
		printf("read header err.ret=%d.\n", ret);
		return -1;
	} else if(ret == 0) {
		printf("peer disconnected.\n");
		return -1;
	}

	// 判断帧头数据长度字段
	if(eth_hdr.len > 0) {
		//	缓冲区大小不够
		if (eth_hdr.len > buf_len) {
			printf("recv buffer len not enough.\n");
			return -1;
		}
		// 读取实际数据
		ret = read(s, buf, eth_hdr.len);
		if(ret < 0) {
			printf("read data err.ret=%d.\n", ret);
			return -1;
		} else if(ret == 0) {
			printf("peer disconnected.\n");
			return -1;
		}
		*recv_len = eth_hdr.len;
	}
	printf("tcp recv[len = %d]:\n", eth_hdr.len);
	return RET_OK;
}

void tcp_close(int32_t s) {
	close(s);
}

int32_t tcp_client_init(uint8_t *host, int16_t port)
{
	struct sockaddr_in addr = {0};
	int32_t socket_fd = -1;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		printf("create socket failed!\n");
		goto err;
	}
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_port = htons(port);
	addr.sin_family = PF_INET;
	addr.sin_addr.s_addr = inet_addr(host);

	int32_t ret = connect(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
	if(ret < 0) {
		printf("connect error!.\n");
		goto err;
	}
	return socket_fd;
err:
	if (socket_fd >= 0)
		tcp_close(socket_fd);
	return -1;
}

int32_t tcp_server_init(int16_t port)
{
	struct sockaddr_in addr = {0};
	int32_t socket_fd = -1;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		printf("create socket failed!\n");
		goto err;
	}
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_port = htons(port);
	addr.sin_family = PF_INET;
	// 0.0.0.0
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		printf("bind error[port=%d]!\n", port);
		goto err;
	}
	if (listen(socket_fd, 5) < 0) {
		printf("listen error!\n");
		goto err;
	}

	int32_t conn_fd = accept(socket_fd, NULL, NULL);
    if(conn_fd < 0) {
        printf("socket accept error!\n");
        goto err;
    }
    return conn_fd;
	
err:
	if (socket_fd >= 0)
		tcp_close(socket_fd);
	return -1;
}