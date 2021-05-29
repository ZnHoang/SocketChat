#ifndef EPOLL_PROCESS_H
#define EPOLL_PROCESS_H

class EpollProcess
{
public:
    EpollProcess();
    ~EpollProcess();

private:
    const int port{8888};
    const int maxConn{10000};
};

#endif