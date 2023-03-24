#ifndef ERR_H
#define ERR_H


//错误代码定义
typedef enum ret_value {
    RET_OK = 0,								//操作成功
    RET_ERR = -1,							//操作异常
    RET_FD_RESET = -2,						//套接字描述符需要重新初始化
} ret_value_t;
	

#endif
