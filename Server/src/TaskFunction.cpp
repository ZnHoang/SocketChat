#include "TaskFunction.h"

void TaskFunction::acceptClient(const int& sfd, MyEpoll& me)
{
    int clitFd;
    struct sockaddr_in clitAddr;
    while(1)
    {
        memset(&clitAddr, 0, sizeof(clitAddr));
        socklen_t len = sizeof(clitAddr);
        if(clitFd = accept(sfd, static_cast<sockaddr*>(static_cast<void*>(&clitAddr)), &len); clitFd == -1)
        {
            if(errno == EAGAIN)
            {
                return ;
            }
            else
            {
                std::cout << strerror(errno);
                return ;
            }
        }
        else
        {
            TaskFunction::setFdNonBl(clitFd);
            if(!MapFd2CS::addStruct(clitFd))
            {
                std::cout << "ERROR CONNECTION\n";
                return ;
            }
            else
            {
                std::shared_ptr<ClientStruct> p;
                MapFd2CS::getPStruct(clitFd, p);
                if(int res = me.setEvent(EPOLL_CTL_ADD, clitFd, EPOLLIN | EPOLLONESHOT); res != 0)
                {
                    std::cout << strerror(res);
                    return ;
                }
                else
                {
                    mRR um;
                    um[ReadFlag::NONE] = ReadFlag::READ;
                    p.get()->setRead(um);
                    char dst[16];
                    printf("NEW CONNECTION:\nIP:%s\nPORT:%d\n\n", inet_ntop(AF_INET, static_cast<void *>(&clitAddr.sin_addr), dst, sizeof(dst)), ntohs(clitAddr.sin_port));
                }
            }
        }
    }
}

void TaskFunction::readMsg(const int& clitFd, MyEpoll& me)
{
    std::shared_ptr<ClientStruct> p;
    MapFd2CS::getPStruct(clitFd, p);
    {
        mRR um;
        um[ReadFlag::READ] = ReadFlag::READING;
        p.get()->setRead(um);
    }
    {
        mWW um;
        if(p.get()->setWrite(um) == WriteFlag::WRITE)
        {
            me.setEvent(EPOLL_CTL_MOD, clitFd, EPOLLOUT | EPOLLONESHOT);
        }
    }
    while(1)
    {
        char buf[1024] = {0};
        int res = recv(clitFd, buf, sizeof(buf), 0);
        std::cout << res << std::endl;
        if(res > 0)
        {
            std::cout << buf << std::endl;
        }
        else if(res == 0)
        {
            //关闭连接以及相关操作
            break;
        }
        else
        {
            if(errno == EAGAIN)
            {
                break;
            }
            break;
        }
    }
    //断开或异常结束其他操作，否则死循
    mWW mww;
    if(p.get()->setWrite(mww) == WriteFlag::WRITE)
    {
        me.setEvent(EPOLL_CTL_MOD, clitFd, EPOLLOUT | EPOLLIN | EPOLLONESHOT);
    }
    else
    {
        int res = me.setEvent(EPOLL_CTL_MOD, clitFd, EPOLLIN | EPOLLONESHOT);
        std::cout << strerror(res) << std::endl;
    }
    mRR mrr;
    mrr[ReadFlag::READING] = ReadFlag::READ;
    p.get()->setRead(mrr);
}

void TaskFunction::setFdNonBl(const int& clitFd)
{
    int oldFl = fcntl(clitFd, F_GETFL);
    fcntl(clitFd, F_SETFL, oldFl | O_NONBLOCK);
}