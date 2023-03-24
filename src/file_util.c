#include "file_util.h"
#include "err.h"
#include "log.h"

uint32_t get_file_size(char *path)
{
    uint32_t size = 0;
    /* 打开文件 */
    FILE *fpr = fopen(path, "r");
    if (fpr == NULL) {
        log_err("open file [%s] error.\n", path);
        return size;
    }
    /* 计算文件大小信息 */
    fseek(fpr, 0L, SEEK_END);
	size = ftell(fpr);
    fclose(fpr);
    return size;
}

uint64_t read_file(char *path, char *buf, uint64_t seq, uint32_t block_size)
{
    FILE *file = fopen(path, "rb");
    if(file == NULL) {
        log_err("open read wrror.\n");
        perror(path);
        return RET_ERR;
    }
    // 移动头
    fseek(file, seq*block_size, SEEK_SET);
    uint32_t read_len = fread(buf, sizeof(char), block_size, file);
    fclose(file);
    return read_len;
}

uint64_t append_file(char *path, char *buf, uint64_t len)
{
    FILE *file = fopen(path, "ab");
    if(file == NULL) {
        log_err("open write wrror.\n");
        perror(path);
        return RET_ERR;
    }
    uint32_t write_len = fwrite(buf, sizeof(char), len, file);
    fflush(file);
    fclose(file);
    return write_len;
}

uint32_t get_file_count(char *dir) {
    DIR *dp;
    int32_t ret_cnt = 0;
    struct dirent *dirp;
    if((dp = opendir(dir)) == NULL) {
        log_err("can't open %s\n", dir);
        closedir(dp);
        return RET_ERR;
    }
        
    while((dirp = readdir(dp)) != NULL)
    {
        if(strcmp(dirp->d_name, ".") == 0 || strcmp(dirp->d_name,"..") == 0) ///current dir OR parrent dir
            continue;
        ++ret_cnt;
    }
    closedir(dp);
    return ret_cnt;
}