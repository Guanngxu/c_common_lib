#ifndef UTILS_H
#define UTILS_H

#define arr_count(array) (sizeof(array) / sizeof(typeof(*array)))

void replace_char(char *str, char src, char dst);

int file_exist(const char *path);

#endif