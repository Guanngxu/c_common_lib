#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdint.h>
#include <stdio.h>


#define BLOCK_SIZE 876

uint64_t read_file(uint8_t *path, uint8_t *buf, uint64_t seq);

uint64_t write_file(uint8_t *path, uint8_t *buf, uint64_t len);

#endif