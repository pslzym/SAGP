#Linux net program

##epoll
epoll 有两种触发方式
*	Level-triggered（默认）
*	edge-triggered

两种方式的内部原理
http://www.cnblogs.com/OnlyXP/archive/2007/08/10/851222.html

epoll使用API
https://zh.wikipedia.org/wiki/Epoll

##select

使用方法
https://zh.wikipedia.org/wiki/Select_(Unix)

* void FD_CLR(int fd, fd_set *set);
* int  FD_ISSET(int fd, fd_set *set);
* void FD_SET(int fd, fd_set *set);
* void FD_ZERO(fd_set *set);

##I/O模型
* 阻塞式IO 需要调用系统函数进行 kernal -> usr数据copy
* 非阻塞式 需要调用系统函数进行 kernal -> usr数据copy
* IO复用（select/poll） 需要调用系统函数进行 kernal -> usr数据copy
* 信号驱动式IO(SIGIO) 需要调用系统函数进行 kernal -> usr数据copy
* 异步IO（aio_系列函数）不需要kernal -> usr数据copy 相关接口已经准备OK

##pselect or ppoll

重要区别是加上了掩码

1.调用pselect 或 ppoll 之前使用进程自己设置的掩码。
2.调用时，采用函数设置的掩码。
3.调用后使用调用函数之前的掩码。
