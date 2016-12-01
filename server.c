#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unisttd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "get_time.h"
#include "init_socket.h"
#include "http_session.h"


int main(int argc, char **argv)
{
    int listenFd, connFd;
    socklen_t clientLen;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    bzero(&serverAddr, sizeof(struct sockaddr_in));
    bzero(&clientAddr, sizeof(struct sockaddr_in));

    if (init_socket(&listenFd, &serverAddr) == -1)
    {
        perror("init_socket() error: in server.c");
        exit(EXIT_FAILURE);
    }

    socklen_t addrLen = sizeof(struct sockaddr_in);
    pid_t pid;

    while (1)
    {
        if (connFd = accept(linstenFd, (struct sockaddr *)&clientAddr, &addrlen) == -1)
        {
            perror("accept() error: in server.c");
            continue;
        }
        if (pid == fork() > 0)
        {
            close(connFd);
            continue;
        }
        else  if (pid == 0)
        {
            close(listenFd);
            printf("pid %d process http session from %s: %d\n", getpid(),
                    inet_ntoa(clientAddr.sin_addr), htons(clientAddr.sin_port));
            if (http_session(&connFd, &clientAddr) == -1)
            {
                perror("http_session() error: in server.c");
                shutdown(connFd, SHUT_RDWR);
                exit(EXIT_SUCCESS);
            }
        }
        else
        {
            perror("fork() error: in server.c");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
