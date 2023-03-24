#ifndef FILE_UTIL_H
#define FILE_UTIL_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <errno.h>
#include <dirent.h>
#include <fcntl.h>

uint32_t get_file_size(char *path);

uint32_t get_file_count(char *dir);

uint64_t append_file(char *path, char *buf, uint64_t len);

uint64_t read_file(char *path, char *buf, uint64_t seq, uint32_t block_size);


#endif