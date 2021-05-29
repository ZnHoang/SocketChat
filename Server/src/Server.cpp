#include "Server.h"

Server::Server()
{
    /*
    struct sockaddr_in sin;
    int sfd = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(sfd, SOL_SOCKET, SO_REUSEPORT, static_cast<const void *>(&opt), sizeof(opt));
    fcntl(sfd, F_SETFL, O_NONBLOCK);
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(port);
    bind(sfd, static_cast<sockaddr*>(static_cast<void*>(&sin)), sizeof(sin));
    listen(sfd, 10000);
    int epfd = epoll_create(maxConn);
    epoll_event epev;
    epev.events = EPOLLIN | EPOLLET;
    epev.data.fd = sfd;
    epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &epev);
    struct epoll_event evListen[maxConn];
    while(1)
    {
        int res = epoll_wait(epfd, evListen, maxConn, 0);
        if(res == -1)
        {
            std::cout << "no\n";
        }
        else if(res == 0)
        {
            continue;
        }
        else
        {
            for(auto i = 0; i < res; i++)
            {
                if(evListen[i].data.fd == sfd && (evListen[i].events & EPOLLIN))
                {
                    struct sockaddr_in clitAddr;
                    memset(&clitAddr, 0, sizeof(clitAddr));
                    socklen_t clitLen = sizeof(clitAddr);
                    int cfd;
                    cfd = accept(sfd, static_cast<sockaddr*>(static_cast<void*>(&clitAddr)), &clitLen);
                    char dst[16];
                    printf("NEW CONNECTION:\nIP:%s\nPORT:%d\n\n", inet_ntop(AF_INET, static_cast<void *>(&clitAddr.sin_addr), dst, sizeof(dst)), ntohs(clitAddr.sin_port));
                    errno = 0;
                    epoll_event epev2;
                    epev2.events = EPOLLIN | EPOLLET;
                    epev2.data.fd = cfd;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &epev2);
                    if(errno != 0)
                    {
                        std::cout << "first  " << strerror(errno);
                        exit(0);
                    }
                    errno = 0;
                    epev2.events = EPOLLOUT | EPOLLET;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &epev);
                    if(errno != 0)
                    {
                        std::cout << "second  " << strerror(errno);
                        exit(0);
                    }
                }
                else
                {

                }
            }
        }
    }
    */
    try{
        myEpoll = {123};
    } catch(int en)
    {
        std::cout << strerror(en);
    }
}

Server::~Server()
{
    
}