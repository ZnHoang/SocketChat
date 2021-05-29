#include "MyEpoll.h"

MyEpoll::MyEpoll(const int& sfd)
    :   sfd(sfd)
{
    if(initEpoll(); epfd > 0)
    {
        throw errno;
    }

}

MyEpoll::~MyEpoll()
{

}

void MyEpoll::initEpoll()
{
    epfd = epoll_create(100000);
}