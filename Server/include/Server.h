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
#include "ThreadPool.h"
class Server
{
public:
    Server();
    ~Server();

private:
    void initServer();
    void initSocketFd();
    void setFdNonBl();
    void Bind();
    void Listen();
    static void task();

    const int PORT{8888};
    const int MAX_CONN{10000};
    int sfd;
    MyEpoll myEpoll;
};

#endif