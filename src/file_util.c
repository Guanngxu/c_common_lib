#include "../inc/file_util.h"

// 以二进制形式按块序列号读取文件内容
uint64_t read_file(uint8_t *path, uint8_t *buf, uint64_t seq)
{
    FILE *file = fopen(path, "rb");
    if(file == NULL) {
        printf("open read wrror.\n");
        perror(path);
        return -1;
    }

    fseek(file, seq*BLOCK_SIZE, SEEK_SET);
    uint64_t read_len = fread(buf, sizeof(uint8_t), BLOCK_SIZE, file);
    fclose(file);
    return read_len;
}

// 以二进制追加文件内容
uint64_t write_file(uint8_t *path, uint8_t *buf, uint64_t len)
{
    FILE *file = fopen(path, "ab");
    if(file == NULL) {
        printf("open write wrror.\n");
        perror(path);
        return -1;
    }
    uint64_t write_len = fwrite(buf, sizeof(uint8_t), len, file);
    fflush(file);
    fclose(file);
    return write_len;
}