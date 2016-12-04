#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int
main(){
    int * p, pid;
    p = malloc(sizeof(int));
    *p = 4;

    printf("parent -> addr:%o , value:%d\n",p, *p);

    pid = fork();
    if (pid == 0){ //child
        printf("child -> addr:%o , value:%d\n",p, *p);
        *p = 5;
        printf("child -> addr:%o , value:%d\n",p, *p);
    } else {
        sleep(10);
        printf("parent -> addr:%o , value:%d\n",p, *p);
    }
}
