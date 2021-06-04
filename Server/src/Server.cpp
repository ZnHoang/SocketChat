#include "Server.h"
Server::Server()
{
    try {
        initServer();
        myEpoll.initEpoll();
        addAcceptEv();
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
    else if(epev.events & EPOLLIN)
    {
        tp.addTask(Priority::LOW, TaskFunction::readMsg, epev.data.fd, myEpoll);
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