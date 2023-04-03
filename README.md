# C 语言常用库

## log_util 日志打印封装

```C
// debug 级别日志
log_debug(fmt, ...);

// info 级别日志
log_info(fmt, ...);

// warn 级别日志
log_warn(fmt, ...);

// error 级别日志
log_err(fmt, ...);
```

## eth_util 以太网封装

```C
// 向套接字发送数据
int32_t tcp_send(int32_t s, char *buf, uint32_t send_len);

// 从套接字接收数据
int32_t tcp_recv(int32_t s, char *buf, int32_t *recv_len);

// 以太网服务端初始化
int32_t tcp_server_init(int16_t port);

// 以太网客户端初始化
int32_t tcp_client_init(char *host, int16_t port);
```

## mem_pool 内存池管理封装

```C
// 内存池初始化
void mempool_init(mempool_info_t *mempool_info);

// 内存池 malloc
void * mempool_malloc(size_t size, mempool_info_t *mempool_info);

// 内存池 free 释放内存
void mempool_free(void* ptr, mempool_info_t *mempool_info);

// 内存池 realloc
void * mempool_realloc(void* ptr, size_t size, mempool_info_t *mempool_info);
```

## file_util 文件操作封装

```C
// 获取文件大小信息
uint32_t get_file_size(char *path);

// 获取指定目录的文件数量
uint32_t get_file_count(char *dir);

// 向指定文件追加内容
uint64_t append_file(char *path, char *buf, uint64_t len);

// 按文件块大小，读取指定文件信息
uint64_t read_file(char *path, char *buf, uint64_t seq, uint32_t block_size);
```

## hash_map 哈希表封装

```C
// 新建哈希表对象
hash_map_t * new_hash_map(size_t size);

// 删除哈希表对象
void del(hash_map_t * d);

// 获取键值对
const char * get(const hash_map_t * d, const long key, const char * def);

// 添加键值对
int put(hash_map_t * d, const long key, const char * val);

// 删除键值对
void remove_item(hash_map_t * d, const long key);

// 打印哈希表
void show_map(hash_map_t * d);
```