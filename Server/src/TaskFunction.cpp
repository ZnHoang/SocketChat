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

void TaskFunction::recvMsg(const int& clitFd, MyEpoll& me)
{
    std::shared_ptr<ClientStruct> p;
    MapFd2CS::getPStruct(clitFd, p);
    if(p == nullptr)
    {
        TaskFunction::closeClient(clitFd, me);
        return ;
    }
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
        if(res > 0)
        {
            //定义消息结构后再进行解析操作
            std::cout << buf << std::endl;
            std::string msg = buf;
            TaskFunction::addSendMsg(msg, clitFd, me);
        }
        else if(res < 0 && errno == EAGAIN)
        {
            break;
        }
        else
        {
            //关闭连接以及相关操作
            TaskFunction::closeClient(clitFd, me);
            return;
        }
    }
    mWW mww;
    int evs = EPOLLIN | EPOLLONESHOT;
    if(p.get()->setWrite(mww) == WriteFlag::WRITE)
    {
        evs |= EPOLLOUT;
    }
    mRR mrr;
    mrr[ReadFlag::READING] = ReadFlag::READ;
    p.get()->setRead(mrr);
    me.setEvent(EPOLL_CTL_MOD, clitFd, evs);
}

void TaskFunction::sendMsg(const int& clitFd, MyEpoll& me)
{
    std::shared_ptr<ClientStruct> p;
    MapFd2CS::getPStruct(clitFd, p);
    if(p == nullptr)
    {
        TaskFunction::closeClient(clitFd, me);
        return ;
    }
    {
        mWW um;
        um[WriteFlag::WRITE] = WriteFlag::WRITING;
        p.get()->setWrite(um);
    }
    {
        mRR um;
        if(p.get()->setRead(um) == ReadFlag::READ)
        {
            me.setEvent(EPOLL_CTL_MOD, clitFd, EPOLLIN | EPOLLONESHOT);
        }
    }
    while(1)
    {
        std::string msg = p.get()->Pop();
        if(msg == "")
        {
            break;
        }
        int res = send(clitFd, msg.c_str(), msg.size(), 0);
        if(res == -1)
        {
            TaskFunction::closeClient(clitFd, me);
            return ;
        }
    }
    int evs = 0;
    if(p.get()->tryPop())
    {
        evs = EPOLLOUT | EPOLLONESHOT;
        mWW mww;
        mww[WriteFlag::WRITING] = WriteFlag::WRITE;
        p.get()->setWrite(mww);
    }
    else
    {
        mWW mww;
        mww[WriteFlag::WRITING] = WriteFlag::NONE;
        p.get()->setWrite(mww);
    }
    mRR mrr;
    if(p.get()->setRead(mrr) == ReadFlag::READ)
    {
        evs |= EPOLLIN;
    }
    me.setEvent(EPOLL_CTL_MOD, clitFd, evs);
}

void TaskFunction::closeClient(const int& clitFd, MyEpoll& me)
{
    me.setEvent(EPOLL_CTL_DEL, clitFd);
    MapFd2CS::delStruct(clitFd);
    close(clitFd);
}

void TaskFunction::addSendMsg(std::string& msg, const int& clitFd, MyEpoll& me)
{
    std::shared_ptr<ClientStruct> p;
    MapFd2CS::getPStruct(clitFd, p);
    if(p == nullptr)
    {
        return ;
    }
    p.get()->Push(msg);
    int evs = EPOLLONESHOT;
    bool isNewEv = false;
    mWW mww;
    mww[WriteFlag::NONE] = WriteFlag::WRITE;
    if(p.get()->setWrite(mww) == WriteFlag::NONE)
    {
        evs |= EPOLLOUT;
        isNewEv = true;
    }
    mRR mrr;
    if(p.get()->setRead(mrr) == ReadFlag::READ)
    {
        evs |= EPOLLIN;
        isNewEv = true;
    }
    if(isNewEv)
    {
        me.setEvent(EPOLL_CTL_MOD, clitFd, evs);
    }
}

void TaskFunction::setFdNonBl(const int& clitFd)
{
    int oldFl = fcntl(clitFd, F_GETFL);
    fcntl(clitFd, F_SETFL, oldFl | O_NONBLOCK);
}