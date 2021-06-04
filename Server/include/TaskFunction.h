#ifndef TASK_FUNCTION_H
#define TASK_FUNCTION_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include "ClientStruct.h"
#include "MyEpoll.h"
#include "MapFd2CS.h"
#include <sys/fcntl.h>
#include <sys/types.h>
#include <unistd.h>

class TaskFunction
{
public:
    TaskFunction() = delete;
    static void acceptClient(const int& sfd, MyEpoll& me);
    static void readMsg(const int& clitFd, MyEpoll& me);




    static void setFdNonBl(const int& clitFd);
};

#endif