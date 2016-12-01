#include "init_socket.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

int init_socket(int *listenFd, struct sockaddr_in *serverAddr)
{
    if ((*listenFd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket() error: in init_socket.c");
        return -1;
    }

    int opt = SO_REUSEADDR;
    if (setsockopt(*listenFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        perror("setsockopt() error: in init_socket.c");
        return -1;
    }

    serverAddr->sin_family = AF_INET;
    serverAddr->sin_port = htos(PORT);
    serverAddr->sin_addr.s_addr = htonl(INADDR_ANY);

    if (-1 == bind(*linstenFd, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr_in)))
    {
        perror("bind() error: in init_socket.c");
        return -1;
    }

    if (-1 == listen(*listenFd, BACKLOG))
    {
        perror("listen() error: in init_socket.c");
        return -1;
    }
    return 0;
}
