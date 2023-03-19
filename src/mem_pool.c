#include "../inc/mem_pool.h"

// 检查内存池是否正确初始化
int32_t check_mempool_info(mempool_info_t *mempool_info) {
	if (mempool_info->block_size <= 0) {
		printf("the block size illegal, please init mempool_info_t first\n");
		return -1;
	}
	if (mempool_info->mempool_size <= 0) {
		printf("the memory pool size is zero, please init mempool_info_t first\n");
		return -1;
	}
	if (mempool_info->block_arr_length == 0) {
		printf("the memory block array length is zero, please init mempool_info_t first\n");
		return -1;
	}
	if (mempool_info->mem_addr == NULL) {
		printf("the memory pool is NULL, please init mempool_info_t first\n");
		return -1;
	}
	if (mempool_info->block_arr == NULL) {
		printf("the memory block array is NULL, please init mempool_info_t first\n");
		return -1;
	}
	return 0;
}

// 找到连续可用的 n 个内存块
void * find_available_blocks(uint32_t n, mempool_info_t *mempool_info) {
	void * addr = NULL;
	uint32_t i, j;
	for (i = 0; i < mempool_info->block_arr_length; i++) {
		/* 从第一个可用的内存块开始查找 */
		if (mempool_info->block_arr[i].available == 1) {
			if (i + n > mempool_info->block_arr_length) {
				printf("the memory pool has run out!\n");
				return addr;
			}
			uint8_t flag = 1;
			for (j = 0; j < n; j++) {
				if (mempool_info->block_arr[i + j].available == 0) {
					flag = 0;
					break;
				}
			}
			if (flag) {
				addr = mempool_info->mem_addr + (i * mempool_info->block_size);
				/* 对每个块包含的信息进行标记 */
				for (j = 0; j < n; j++) {
					mempool_info->block_arr[i + j].available = 0;
					/* 关联包括自己本身 */
					mempool_info->block_arr[i + j].related = n - j;
				}
				return addr;
			}
		}
	}
	return NULL;
}


// 初始化内存池函数
void mempool_init(mempool_info_t *mempool_info) {
	int32_t i;
	if (check_mempool_info(mempool_info) == 0) {
		printf("please init mempool_info_t before mempool_init\n");
		return;
	}
	uint32_t len = mempool_info->mempool_size / mempool_info->block_size;
	if (len > mempool_info->block_arr_length) {
		printf("the block_arr_length is smaller than mempool_size/block_size, %d memory will be wasted\n", (len - mempool_info->block_arr_length)*mempool_info->block_size);
		len = mempool_info->block_arr_length;
	}
	else {
		mempool_info->block_arr_length = len;
	}
	for (i = 0; i < mempool_info->block_arr_length; i++) {
		mempool_info->block_arr[i].available = 1;
		mempool_info->block_arr[i].related = 0;
	}
	printf("memory pool inited\n");
}

// malloc 函数
void * mempool_malloc(size_t size, mempool_info_t *mempool_info) {
	if (size <= 0) {
		printf("size illegal\n");
		return NULL;
	}
	if (!check_mempool_info(mempool_info)) {
		printf("the memory pool not inited, please call mempool_init before mempool_malloc");
	}
	uint32_t n = (size % mempool_info->block_size == 0) ? (size / mempool_info->block_size) : (size / mempool_info->block_size + 1);
	return find_available_blocks(n, mempool_info);
}



// realloc 函数
void * mempool_realloc(void* ptr, size_t size, mempool_info_t *mempool_info) {
	if (ptr == NULL) {
		printf("erro :you realloc a NULL pointer\n");
		return NULL;
	}
	// TODO: 重新分配的大小和原大小一样
	int32_t n = (size%mempool_info->block_size == 0) ? (size / mempool_info->block_size) : (size / mempool_info->block_size + 1);
	if ((ptr - mempool_info->mem_addr) % mempool_info->block_size != 0) {
		printf("please mempool_realloc a right pointer\n");
		return NULL;
	}
	int32_t i = (ptr - mempool_info->mem_addr) / mempool_info->block_size;
	if (mempool_info->block_arr[i].related == 0) {
		printf("The current memory block has been freed\n"); 
		return NULL;
	}
	if (mempool_info->block_arr[i].related == n) {
		return ptr;
	}
	mempool_free(ptr, mempool_info);
	return mempool_malloc(size, mempool_info);
}

// free 函数
void mempool_free(void* ptr, mempool_info_t *mempool_info) {
	if (ptr == NULL) {
		printf("error: you free a NULL pointer\n");
		return;
	}
	if ((ptr - mempool_info->mem_addr) % mempool_info->block_size != 0) {
		printf("please free a right ptr which you had malloc by mempool_malloc\n");
		return;
	}
	size_t offset = ptr - mempool_info->mem_addr;
	uint32_t index = offset / mempool_info->block_size;
	uint32_t related = mempool_info->block_arr[index].related;
	int32_t j;
	if (mempool_info->block_arr[index].related == 0) {
		printf("current block has been freed\n");
		return;
	}
	/* 如果有与之相关联的块，则将其全部标记为可用状态 */
	for (j = 0; j < related; j++) {
		mempool_info->block_arr[index + j].related = 0;
		mempool_info->block_arr[index + j].available = 1;
	}
}
