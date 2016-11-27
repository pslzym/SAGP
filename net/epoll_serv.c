#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

#include "utils.h"
#include "help.h"

int main()
{
    struct sockaddr_in serv_addr;
    int serv_fd, epoll_fd;

    memset(&serv_addr, 0, sizeof(serv_addr));

    if (inet_pton(AF_INET, TCP_SRV_ADDR, &serv_addr.sin_addr.s_addr) == -1){
        perror("inet_pton");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(TCP_SRV_PORT);

    if ((serv_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        perror("socket");
        exit(1);
    }

    //set non blocking
    setnonblocking(serv_fd);

    if (bind(serv_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1){
        perror("bind");
        exit(1);
    }
    printf("bind success.\n");

    if (listen(serv_fd, 5) == -1){
        perror("listen");
        exit(-1);
    }
    printf("listen function success.\n");

    //set epoll
    struct epoll_event ev, events[MAX_EVENTS];

    if ((epoll_fd = epoll_create1(0)) == -1){
        perror("epoll_create1");
        exit(1);
    }

    ev.data.fd = serv_fd;
    ev.events = EPOLLIN | EPOLLET;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, serv_fd, &ev) == -1){
        perror("epoll_ctl");
        exit(1);
    }

    while(1){
        int nfds, i;
        struct sockaddr_in client_addr;
        int client_fd;
        socklen_t len = sizeof(client_fd);
        //timeout = -1 is block
        printf("epoll wait.\n");
        if ((nfds = epoll_wait(epoll_fd, events, MAX_EVENTS, -1)) == -1){
            perror("epoll_wait");
            exit(1);
        }
        printf("epoll wait success, nfds : %d.\n", nfds);
        for (i = 0; i < nfds; i++){
            // fd equal serv_fd
            //struct epoll_event ev;
            if((events[i].events & EPOLLERR) || 
                (events[i].events & EPOLLHUP) || 
                (!(events[i].events & EPOLLIN))){
                perror("A fd error.");
                if(epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL) == -1){
                    perror("epoll_ctl del");
                    exit(1);
                }
                close(events[i].data.fd);
                continue;
            } else if (events[i].data.fd == serv_fd){
                printf("nfds is serv_fd.\n");
                client_fd = accept(serv_fd, (struct sockaddr *)&client_addr, &len);
                if (client_fd == -1){
                    //some can again error or EINTR signal
                    if (errno == EAGAIN || errno == EWOULDBLOCK || errno == EINTR){
                        continue;
                    } else {
                        perror("accept");
                        continue;
                    }
                }
                //set the client_fd into epoll_fd
                setnonblocking(client_fd);
                ev.data.fd = client_fd;
                ev.events = EPOLLIN | EPOLLET;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &ev) == -1){
                    perror("epoll_ctl");
                    exit(1);
                }
            } else {
                printf("nfds is tcp connect.\n");
                ssize_t count, wn;
                char buf[512];
                int flag = 0;
                while(1){
                    count = read(events[i].data.fd, buf, sizeof buf);
                    if (count == -1 && errno == EINTR){
                        continue;
                    }
                    else if (count == -1 && errno == EAGAIN){
                        perror("read");
                        flag = 1;
                        break;
                    } else if (count == 0){
                        flag = 1;
                        break;
                    } else {
                        break;
                    }
                }
                //write data to stdout
                if (count > 0){
                    while(1){
                        wn = write(STDOUT_FILENO, buf, count);
                        if (wn == -1){
                            if (errno == EINTR){
                                continue;
                            } else {
                                perror("write");
                                exit(0);
                            }
                        } else {
                            break;
                        }
                    }
                }
                //close the fd //end of file or read all data.
                if (flag){
                    printf("closed the connection fd : %d.\n", events[i].data.fd);
                    close(events[i].data.fd);
                }

            }
        }
    }
    close(epoll_fd);
    return 0;
}
