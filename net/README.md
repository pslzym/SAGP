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

##malloc/calloc/ralloc
```malloc函数可以从堆上获得指定字节的内存空间
   calloc函数返回值为void型指针。如果执行成功，函数从堆上获得size X n的字节空间，并返回该空间的首地址。该函数与malloc函数的一个显著不同时是，calloc函
   数得到的内存空间是经过初始化的，其内容全为0。calloc函数适合为数组申请空间，可以将size设置为数组元素的空间长度，将n设置为数组的容量。
   realloc函数的功能比malloc函数和calloc函数的功能更为丰富，可以实现内存分配和内存释放的功能，其函数声明如下：
   void * realloc(void * p,int n);
   其中，指针p必须为指向堆内存空间的指针，即由malloc函数、calloc函数或realloc函数分配空间的指针。realloc函数将指针p指向的内存块的大小改变为n字节。如    果n小于或等于p之前指向的空间大小，那么。保持原有状态不变。如果n大于原来p之前指向的空间大小，那么，系统将重新为p从堆上分配一块大小为n的内存空间，同      时，将原来指向空间的内容依次复制到新的内存空间上，p之前指向的空间被释放。relloc函数分配的空间也是未初始化的。
```
