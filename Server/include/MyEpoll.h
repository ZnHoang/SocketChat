#ifndef MY_EPOLL_H
#define MY_EPOLL_H

#include <sys/epoll.h>
#include <error.h>
#include <string.h>
#include <iostream>

class MyEpoll
{
public:
    MyEpoll() = default;
    // MyEpoll(const int& sfd);
    ~MyEpoll();
    void initEpoll();
    void Round();

private:

    int epfd;
    int sfd;
};

#endif