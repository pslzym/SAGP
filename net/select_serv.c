#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <sys/time.h>
#include <arpa/inet.h>

#include "help.h"

#define FD_SIZE 20
#define RBUF_SIZE 20

int main()
{
    struct sockaddr_in serv_addr;
    int serv_fd, client_fds[FD_SIZE];
    socklen_t socklen = sizeof(serv_addr);

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

    fd_set allset, rset;
    FD_ZERO(&allset);
    FD_SET(STDIN_FILENO, &allset);
    FD_SET(serv_fd, &allset);

    int nread, i, connfd;
    FILE * fd;
    char buf[RBUF_SIZE];

    int max_fd = serv_fd;
    memset(client_fds, -1, FD_SIZE);
    memset(buf, 0, RBUF_SIZE);

    while(1){
        rset = allset;
        if ((nread = select(max_fd + 1, &rset, NULL, NULL, NULL)) == -1){ //block fd read
            if (errno == EINTR){
                continue;
            } else {
                perror("select");
                exit(1);
            }
        }

        if (FD_ISSET(serv_fd, &rset)){
            connfd = accept(serv_fd, (struct sockaddr *)&serv_addr, &socklen);
            if (connfd == -1){
                if (errno == EINTR){
                    continue;
                } else {
                    perror("accept");
                    exit(1);
                }
            } else {
                for (i = 0; i < FD_SIZE; i++){
                    if (client_fds[i] == 0 || client_fds[i] == -1){
                        client_fds[i] = connfd;
                        break;
                    }
                }
                if (max_fd < connfd){
                    max_fd = connfd;
                }
                FD_SET(connfd, &allset);
                if (--nread <= 0)
                    continue;
            }
        }

        if (FD_ISSET(STDIN_FILENO, &rset)){
            if(NULL == fgets(buf, RBUF_SIZE, fd)){
                perror("fgets");
            } else {
                fputs(buf, fd);
            }
            if (--nread <= 0)
                continue;
        }
        //handle the client request
        int nread;
        for (i = 0; i < FD_SIZE; i++){
            if (client_fds[i] == -1){
                break;
            }
            if (client_fds[i] == 0){
                continue;
            }
            if (FD_ISSET(client_fds[i], &rset)){
                memset(buf, 0, RBUF_SIZE);
                if ((nread = read(client_fds[i], buf, RBUF_SIZE)) == -1){
                    //handle the error
                    if (errno == EINTR){
                        continue;
                    } else {
                        //handle close fd
                        close(client_fds[i]);
                        FD_CLR(client_fds[i], &allset);
                        client_fds[i] = 0;
                    }
                } else if (nread == 0){
                    //handle close fd
                    close(client_fds[i]);
                    FD_CLR(client_fds[i], &allset);
                    client_fds[i] = 0;
                } else {
                    fputs(buf, stdout);
                    if (--nread <= 0)
                        continue;
                }
            }
        }
    }
}
