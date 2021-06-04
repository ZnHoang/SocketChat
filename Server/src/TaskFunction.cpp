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
                    std::unordered_map<ReadFlag, ReadFlag> um;
                    um[ReadFlag::NONE] = ReadFlag::READ;
                    p.get()->setRead(um);
                    char dst[16];
                    printf("NEW CONNECTION:\nIP:%s\nPORT:%d\n\n", inet_ntop(AF_INET, static_cast<void *>(&clitAddr.sin_addr), dst, sizeof(dst)), ntohs(clitAddr.sin_port));
                }
            }
        }
        std::cout << "fucl\n";
    }
}