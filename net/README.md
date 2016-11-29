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
