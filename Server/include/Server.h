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
#include <vector>
#include "ClientStruct.h"
#include "TaskFunction.h"

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
    void addAcceptEv();
    void resetVEpEvs();
    void dealEvent(const epoll_event epev);
    static void task(const int& fd);
    const int task2();

    int sfd;
    MyEpoll myEpoll;
    ThreadPool tp{MAX_THREAD};
    std::mutex mtMapFd2Msg;
    std::unordered_map<int, std::shared_ptr<ClientStruct>> mapFd2Msg;
    std::vector<epoll_event> vEpEvs;
};

#endif