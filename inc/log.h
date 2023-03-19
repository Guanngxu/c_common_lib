#ifndef LOG_H
#define LOG_H
#include "utils.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define DECLARE_LOGLEVEL_VAR() \
    int32_t _log_level_ = LOG_LVL_INFO

extern int32_t _log_level_;

#define set_loglevel(loglevel)       		\
    do {                             		\
        if (loglevel >= LOG_LVL_DEBUG)     		\
            _log_level_ = LOG_LVL_DEBUG; 		\
        else if (loglevel < LOG_LVL_ERR)    \
            _log_level_ = LOG_LVL_ERR; 		\
        else                         		\
            _log_level_ = loglevel;  		\
    } while (0)

#define get_loglevel() _log_level_
typedef enum {
    LOG_LVL_ERR,
    LOG_LVL_WARN,
    LOG_LVL_INFO,
    LOG_LVL_DEBUG,
} log_level_t;

char *get_loglevel_name(log_level_t level);

int32_t set_log_stdout(char *file);
#define is_debug_mode() (get_loglevel() == LOG_LVL_DEBUG)
#define log_to_stdout(dst_level, fmt, ...)                                      \
    do {                                                                        \
        if (dst_level <= _log_level_) {                                         \
            char proc_buf[256];                                               \
            time_t rawtime;                                                     \
            struct tm timeinfo;                                                 \
            time(&rawtime);                                                     \
            localtime_r(&rawtime, &timeinfo);                                   \
            printf("[%04d-%02d-%02d %02d:%02d:%02d][%s][%s][%s:%d)]" fmt,           		\
                timeinfo.tm_year + 1900, timeinfo.tm_mon + 1, timeinfo.tm_mday, \
                timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec,             \
                get_loglevel_name(dst_level), get_curr_proc_name(proc_buf, sizeof(proc_buf)), 	\
                __FILE__, __LINE__, ##__VA_ARGS__);               \
        }                                                                       \
    } while (0)

#define log_debug(fmt, ...) \
    log_to_stdout(LOG_LVL_DEBUG, fmt, ##__VA_ARGS__)

#define log_info(fmt, ...) \
    log_to_stdout(LOG_LVL_INFO, fmt, ##__VA_ARGS__)

#define log_warn(fmt, ...) \
    log_to_stdout(LOG_LVL_WARN, fmt, ##__VA_ARGS__)

#define log_err(fmt, ...) \
    log_to_stdout(LOG_LVL_ERR, fmt, ##__VA_ARGS__)

#endif
