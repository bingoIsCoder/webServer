#ifndef INIT_SOCKET_H_
#define INIT_SOCKET_H_

#include <netinet/in.h>

#define BACKLOG 20
#define PORT 8080

int init_socket(int *linstenFd, struct sockaddr_in * serverAddr);

#endif
