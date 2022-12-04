#ifndef MEM_POOL_H
#define MEM_POOL_H

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// 内存块数据结构
typedef struct {
	uint32_t available:1; // 当前块是否可用
	uint32_t related:31; // 后续有多少个块与当前块相连
} mem_control_block_t;

// 内存池信息结构
typedef struct {
	uint8_t block_size; // 分配内存块大小
	uint32_t mempool_size; // 内存池大小
	uint32_t block_arr_length; // 数组可访问长度
	void *mem_addr; // 内存池首地址
	mem_control_block_t *block_arr; // 内存块数组
} mempool_info_t;


void mempool_init(mempool_info_t *mempool_info);

void * mempool_malloc(size_t size, mempool_info_t *mempool_info);

void mempool_free(void* ptr, mempool_info_t *mempool_info);

void * mempool_realloc(void* ptr, size_t size, mempool_info_t *mempool_info);

#endif