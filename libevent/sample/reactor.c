#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

#define SERV_PORT 8000L
#define MAX_EVENTS 1024L
#define BUFFLEN 1024L

struct myevent_s
{
    int fd;
    int events;
    void *args;
    void (*cmd)(int fd, int events, void *args);
    int status;
    char buf[BUFFLEN];
    int len;
    long last_active;
};

typedef struct myevent_s myevent_t;

void acceptCmd(int fd, int events, void *args);
void eventadd(int fd, int way, myevent_t * ev);
void eventset(myevent_t * ev, int fd, void (*cmd)(int, int, void *), void * args);
void initListenSocket(const int g_efd, const unsigned short port);
void recvdata(int fd, int events, void * args);
void senddata(int fd, int events, void *args);
void eventdel(int efd, myevent_t * ev);

int g_efd;
myevent_t g_events[MAX_EVENTS + 1];

int main(int argc, char *argv[])
{
    unsigned short port = SERV_PORT;

    if (argc == 2)
        port = atoi(argv[1]);

    g_efd = epoll_create(MAX_EVENTS + 1);

    if (g_efd <= 0)
    {
        printf("create efd in %s err %s\n", __func__, strerror(errno));
    }

    initListenSocket(g_efd, port);

    struct epoll_event wait_events[MAX_EVENTS + 1];

    int i, flag = 1;
    while(flag)
    {
        int nfd = epoll_wait(g_efd, wait_events, MAX_EVENTS + 1, -1);
        printf("epoll_wait num %d\n", nfd);
        for (i = 0; i < nfd; i++)
        {
            myevent_t *ev = wait_events[i].data.ptr; // 取出事件对应的数据
            if ((wait_events[i].events & EPOLLIN) && (ev->events & EPOLLIN))
            {
                ev->cmd(ev->fd, wait_events[i].events, ev->args);
            }
            else if ((wait_events[i].events & EPOLLOUT) && (ev->events & EPOLLOUT))
            {
                ev->cmd(ev->fd, wait_events[i].events, ev->args);
            } else {
                printf("wait: %d, ev : %d\n", wait_events[i].events, ev->events);
                perror("epoll for error");
            }
        }
    }

    return 0;

}

void initListenSocket(const int g_efd, const unsigned short port)
{
    int sfd = socket(AF_INET, SOCK_STREAM, 0);

    fcntl(sfd, F_SETFL, O_NONBLOCK);

    eventset(&g_events[MAX_EVENTS], sfd, acceptCmd, &g_events[MAX_EVENTS]);

    eventadd(g_efd, EPOLLIN, &g_events[MAX_EVENTS]); //水平触发方式

    struct sockaddr_in sin;

    memset(&sin, 0, sizeof(sin));

    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    bind(sfd, (struct sockaddr *)&sin, sizeof(sin));

    listen(sfd, 20);

    return ;
}

void eventset(myevent_t * ev, int fd, void (*cmd)(int, int, void *), void * args)
{
    ev->fd = fd;
    ev->events = 0; //no use 
    ev->args = args;
    ev->cmd = cmd;
    ev->status = 0;
    ev->last_active = time(NULL);

    return ;
}

void eventadd(int fd, int way, myevent_t * ev)
{
    struct epoll_event epev = {0, {0}};
    int op;

    epev.data.ptr = ev;
    epev.events = ev->events = way; // set myevent events

    if (ev->status == 1)
    {
        op = EPOLL_CTL_MOD;
    } else {
        op = EPOLL_CTL_ADD;
        ev->status = 1;
    }

    if((epoll_ctl(fd, op, ev->fd, &epev)) == -1)
        printf("event add failed [fd=%d], events[%d]\n", ev->fd, way);
    else
        printf("event add OK [fd=%d], events[%d]\n", ev->fd, way);

    return ;
}

void acceptCmd(int fd, int events, void *args)
{
    struct sockaddr_in sin;
    socklen_t len = sizeof(sin);
    int cfd, i;

    if ((cfd = accept(fd, (struct sockaddr *)&sin, &len)) == -1)
    {
        if (errno != EAGAIN && errno != EINTR){
            perror("accecpt signal arise!");
        } else {
            printf("%s : accept, %s\n", __func__, strerror(errno));
        }
        return ;
    }

    do
    {
        for (i = 0; i< MAX_EVENTS; i++)
        {
            if (g_events[i].status != 1)
            {
                break;
            }
        }

        if (i == MAX_EVENTS)
        {
            printf("%s : max connect limit[%d]\n", __func__, MAX_EVENTS);
            break;
        }

        int flag = 0;
        if ((flag = fcntl(cfd, F_SETFL, O_NONBLOCK)) < 0)
        {
            printf("%s: fcntl nonblocking failed, %s\n", __func__, strerror(errno));
            break;
        }

        eventset(&g_events[i], cfd, recvdata, &g_events[i]);
        eventadd(g_efd, EPOLLIN, &g_events[i]);
    } while (0);

    printf("new connect [time:%ld], [pos:%d]\n", g_events[i].last_active, i);
    return ;
}

void recvdata(int fd, int events, void * args)
{
    myevent_t * ev = (myevent_t * )args;
    int len;

    len = read(fd, ev->buf, sizeof(ev->buf));

    eventdel(g_efd, ev);

    if (len > 0)
    {
        ev->len = len;
        ev->buf[len] = '\0';
        printf("recv num: %d , data:  %s\n", len, ev->buf);
        eventset(ev, fd, senddata, ev);
        eventadd(g_efd, EPOLLOUT, ev);
    } else if (len == 0) {
        shutdown(ev->fd, SHUT_RD);
        printf("Closed connect [fd:%d], [pos:%d]\n", ev->fd, (int)(ev-g_events));
    } else {
        close(ev->fd);
        perror("recvdata read");
    }

    return ;
}

void senddata(int fd, int events, void *args)
{
    myevent_t * ev = (myevent_t * )args;
    int len;

    len = write(fd, ev->buf, ev->len);

    eventdel(g_efd, ev);

    if(len > 0)
    {
        printf("write : %d data : %s\n", len, ev->buf);
        eventset(ev, fd, recvdata, ev);
        eventadd(g_efd, EPOLLIN, ev);
    } else {
        close(fd);
        perror("senddata");
    }

    return ;
}

void eventdel(int efd, myevent_t * ev)
{
    struct epoll_event epv = {0, {0}};
    if (ev->status != 1)
    {
        return ;
    }

    epv.data.ptr = ev;
    ev->status = 0;

    epoll_ctl(efd, EPOLL_CTL_DEL, ev->fd, &epv);

    return ;
}
