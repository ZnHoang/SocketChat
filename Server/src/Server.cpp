#include "Server.h"
Server::Server()
{
    /*
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
    try {
        initServer();
        myEpoll.initEpoll();
        addAcceptEv();
        tp.addTask(Priority::MIDDLE, task, sfd);
    } catch(int en) {
        throw;
    }
}

Server::~Server()
{
    
}

void Server::Start()
{
    while(1)
    {
        resetVEpEvs();
        vEpEvs = myEpoll.Check();
        std::cout << vEpEvs.size() << std::endl;
        for(const auto v : vEpEvs)
        {
            dealEvent(v);
        }
    }
}

void Server::initServer()
{
    try {
        initSocketFd();
        setFdNonBl();
        Bind();
        Listen();
    } catch(int en) {
        throw;
    }
}

void Server::initSocketFd()
{
    if(sfd = socket(AF_INET, SOCK_STREAM, 0); sfd == -1)
    {
        throw errno;
    }
    int opt = 1;
    if(int res = setsockopt(sfd, SOL_SOCKET, SO_REUSEPORT, static_cast<const void *>(&opt), sizeof(opt)); res == -1)
    {
        throw errno;
    }
}

void Server::setFdNonBl()
{
    int oldFl = 0;
    if(oldFl = fcntl(sfd, F_GETFL); oldFl == -1)
    {
        throw errno;
    }
    if(int res = fcntl(sfd, F_SETFL, oldFl | O_NONBLOCK); res == -1)
    {
        throw errno;
    }
}

void Server::Bind()
{
    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);
    if(int res = bind(sfd, static_cast<sockaddr*>(static_cast<void*>(&sin)), sizeof(sin)); res == -1)
    {
        throw errno;
    }
}

void Server::Listen()
{
    if(int res = listen(sfd, MAX_CONN); res == -1)
    {
        throw errno;
    }
}

void Server::addAcceptEv()
{
    int op = EPOLL_CTL_ADD;
    int evs = EPOLLIN | EPOLLET;
    if(int en = myEpoll.setEvent(op, sfd, evs); en != 0)
    {
        throw en;
    }
}

void Server::resetVEpEvs()
{
    vEpEvs.clear();
}

void Server::dealEvent(const epoll_event epev)
{
    if(epev.data.fd == sfd)
    {
        tp.addTask(Priority::HIGH, TaskFunction::acceptClient, sfd, myEpoll);
    }
    else
    {

    }
}

void Server::task(const int& fd)
{
    std::cout << std::this_thread::get_id() << std::endl;
    std::cout << fd << std::endl;
}

const int Server::task2()
{
    int a = 10;
    return a;
}