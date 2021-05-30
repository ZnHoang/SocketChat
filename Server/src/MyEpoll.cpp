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