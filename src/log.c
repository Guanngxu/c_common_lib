#include "log.h"

typedef struct {
    int32_t level;
    char name[64];
} log_level_info_t;

__attribute__((weak)) int32_t _log_level_ = LOG_LVL_INFO;

static log_level_info_t li[] = {
    { LOG_LVL_ERR, "ERROR" },
    { LOG_LVL_WARN, "WARN" },
    { LOG_LVL_INFO, "INFO" },
    { LOG_LVL_DEBUG, "DEBUG" },
};

inline char *get_loglevel_name(log_level_t level)
{
    if (level < LOG_LVL_ERR || level > LOG_LVL_DEBUG)
        return "NULL";
    else
        return li[level].name;
}

int32_t set_log_stdout(char *file)
{
    int32_t fd;

    if (!file)
        return 0;

    fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0666);

    if (fd < 0)
        goto err;

    if (dup2(fd, STDOUT_FILENO) == -1)
        goto err;
    close(fd);
    return 0;

err:
    if (fd >= 0)
        close(fd);

    return -1;
}
