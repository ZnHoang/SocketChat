#include "MyEpoll.h"

MyEpoll::~MyEpoll()
{

}

void MyEpoll::initEpoll()
{
    if(epfd = epoll_create(100000); epfd == -1)
    {
        throw errno;
    }
}

const std::vector<epoll_event>&& MyEpoll::Check()
{
    epoll_event epevs[100000];
    int res;
    if(res = epoll_wait(epfd, epevs, 100000, 1000); res == -1)
    {
        throw errno;
    }
    return std::vector<epoll_event>(epevs, epevs + res);
}

const int&& MyEpoll::setEvent(const int& op, const int& listenFd, const int& evs)
{
    epoll_event epev = createEpEv(listenFd, evs);
    return epoll_ctl(epfd, op, listenFd, &epev) == 0 ? 0 : errno;
}

const epoll_event MyEpoll::createEpEv(const int& listenFd, const int& op)
{
    epoll_event epev;
    epev.data.fd = listenFd;
    epev.events = op;
    return epev;
}