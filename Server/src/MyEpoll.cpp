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

void MyEpoll::Round()
{
    epoll_event epevs[100000];
    int res = epoll_wait(epfd, epevs, 100000, 100);
}