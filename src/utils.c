#include "utils.h"

/**
 * @brief 获取当前进程名
 * @param[in] data 用来存放获取到的进程名
 * @param[in] len data可用的长度
 * @return data
 */
char *get_curr_proc_name(char *data, int32_t len)
{
    int32_t ret;
    char *p;
    char buf[1024] = { 0 };

	//获取当前进程的可执行文件的绝对路径，如/work/code/tets/a.out
    ret = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
    if (ret < 0)
        return "NULL";

    buf[ret] = '\0';

    //如果 buf="/work/code/tets/a.out",通过下面的步骤得到"a.out"
    p = strrchr(buf, '/');
    if (p)
        snprintf(data, len, "%s", p + 1);
    else
        snprintf(data, len, "%s", buf);

    //then data=a.out
    return data;
}