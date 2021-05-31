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
#include <unistd.h>
#include <unordered_map>

const int PORT{8888};
const int MAX_CONN{10000};
const uint MAX_THREAD{3};

class Server
{
public:
    Server();
    ~Server();
    void Start();
private:
    void initServer();
    void initSocketFd();
    void setFdNonBl();
    void Bind();
    void Listen();
    static void task(const int& fd);

    int sfd;
    MyEpoll myEpoll;
    ThreadPool tp{MAX_THREAD};
    using pQueMsg = std::shared_ptr<std::queue<std::string>>;
    std::unordered_map<int, pQueMsg> fd2Msg;
};

#endif