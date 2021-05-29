#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <sys/epoll.h>
#include <arpa/inet.h>
#include <string>
#include <fcntl.h>
#include <string.h>
#include <iostream>
#include <error.h>
#include "MyEpoll.h"

class Server
{
public:
    Server();
    ~Server();

private:
    const int port{8888};
    const int maxConn{10000};
    MyEpoll myEpoll;
};

#endif