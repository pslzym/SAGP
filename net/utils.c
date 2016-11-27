#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "utils.h"

int setnonblocking(int fd)
{
    if (fcntl(fd, F_SETFL, fcntl(fd, F_GETFL, 0)|O_NONBLOCK) == -1)
    {
        perror("fcntl set NONBLOCKING");
        return -1;
    }
    return 0;
}
