#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>

#define REQMAXLEN 512
#define RESMAXLEN 512

void send_to_svr(int, const char *);
void con(int , struct sockaddr_in);


int main(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == -1){
        perror("socket");
        exit(1);
    }
    struct sockaddr_in svraddr;
    bzero(&svraddr, sizeof(svraddr));
    svraddr.sin_family = AF_INET;
    in_addr_t s_addr = inet_addr("192.168.0.130");
    if(s_addr == -1){
        perror("inet_addr");
        exit(1);
    }
    svraddr.sin_addr.s_addr = s_addr;
    svraddr.sin_port = htons(9000);
    char sendbuf[REQMAXLEN+1];

    con(sock, svraddr);
    strcpy(sendbuf, "login");
    send_to_svr(sock, sendbuf);
    close(sock);

}

void con(int sock, struct sockaddr_in svraddr)
{
    int err_code = connect(sock, (struct sockaddr *)&svraddr, sizeof(svraddr));
    if(err_code == -1){
        perror("connect");
        exit(1);
    }
}

void send_to_svr(int sockfd, const char * sendbuf){
    char recvbuf[RESMAXLEN+1];
    size_t sendbuf_len = strlen(sendbuf);
    ssize_t length = write(sockfd, sendbuf, sendbuf_len);
    if(length == -1){
        perror("write");
        close(sockfd);
        exit(1);
    }
    else if(length != sendbuf_len){
        perror("write loss");
        close(sockfd);
        exit(1);
    }
    printf("send to server: %s\n", sendbuf);
    /*ssize_t rec_len = read(sockfd, recvbuf, RESMAXLEN);
    if(rec_len == -1){
        perror("read");
        close(sockfd);
        exit(1);
    }
    recvbuf[rec_len] = '\0';
    printf("recv from server: [%zd] %s\n", rec_len, recvbuf);*/
}
