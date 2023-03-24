#include "eth_util.h"
#include "err.h"
#include "log.h"

int32_t tcp_send(int32_t s, char *buf, uint32_t send_len) {
	int32_t ret;

	eth_hdr_t eth_hdr = {0};
	// 转换主机字节序为网络字节序
	eth_hdr.len = htonl(send_len);

	// 发送帧头
	ret =  write(s, (char *)&eth_hdr, sizeof(eth_hdr_t));
	if(ret <= 0) {
		log_err("write header err[ret = %d].\n", ret);
		return RET_ERR;
	}

	// 发送实际数据
	ret =  write(s, buf, send_len);
	if(ret <= 0) {
		log_err("write data err[ret = %d].\n", ret);
		return RET_ERR;
	}
	return ret;
}

int32_t tcp_recv(int32_t s, char *buf, int32_t *recv_len) {
	int32_t ret;
	eth_hdr_t eth_hdr = {0};

	// 读取帧头
	ret =  read(s, (char *)&eth_hdr, sizeof(eth_hdr_t));
	if(ret < 0) {
		log_err("read header err.ret=%d.\n", ret);
		return RET_ERR;
	} else if(ret == 0) {
		log_info("peer disconnected.\n");
		return RET_FD_RESET;
	}
	// 转换网络字节序为主机字节序
	eth_hdr.len = ntohl(eth_hdr.len);

	// 判断帧头数据长度字段
	if(eth_hdr.len > 0) {
		// 需要 判断 len 是否比 buffer 长度长，纯内部使用，暂不加
		ret = read(s, buf, eth_hdr.len);
		if(ret < 0) {
			log_err("read data err.ret=%d.\n", ret);
			return RET_ERR;
		} else if(ret == 0) {
			log_info("peer disconnected.\n");
			return RET_FD_RESET;
		}
		*recv_len = eth_hdr.len;
	}
	log_info("tcp recv[len = %d]:\n", eth_hdr.len);
	return RET_OK;
}

int32_t tcp_client_init(char *host, int16_t port)
{
	struct sockaddr_in addr = {0};
	int32_t socket_fd = -1;

	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		log_err("create socket failed!\n");
		goto err;
	}
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_port = htons(port);
	addr.sin_family = PF_INET;
	addr.sin_addr.s_addr = inet_addr(host);

	int32_t ret = connect(socket_fd, (struct sockaddr *)&addr, sizeof(addr));
	if(ret < 0) {
		log_err("connect error!.\n");
		goto err;
	}
	return socket_fd;
err:
	if (socket_fd >= 0)
		close(socket_fd);
	return RET_ERR;
}

int32_t tcp_server_init(int16_t port)
{
	struct sockaddr_in addr = {0};
	int32_t socket_fd = -1;
	socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0) {
		log_err("create socket failed!\n");
		goto err;
	}
	
	memset(&addr, 0, sizeof(addr));
	addr.sin_port = htons(port);
	addr.sin_family = PF_INET;
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(socket_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		log_err("bind error[port=%d]!\n", port);
		goto err;
	}
	if (listen(socket_fd, 5) < 0) {
		log_err("listen error!\n");
		goto err;
	}
	return socket_fd;
	
err:
	if (socket_fd >= 0)
		close(socket_fd);
	return RET_ERR;
}