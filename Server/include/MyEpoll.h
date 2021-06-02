#ifndef MY_EPOLL_H
#define MY_EPOLL_H

#include <sys/epoll.h>
#include <error.h>
#include <string.h>
#include <iostream>
#include <vector>

class MyEpoll
{
public:
    MyEpoll() = default;
    ~MyEpoll();
    void initEpoll();
    const std::vector<epoll_event>&& Check();
    const int&& setEvent(const int& op, const int& listenFd, const int& evs = 0);

private:
    const epoll_event createEpEv(const int& listenFd, const int& op);

    int epfd;
    int sfd;
};

#endif