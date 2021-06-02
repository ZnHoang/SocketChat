#ifndef CLIENT_STRUCT_H
#define CLIENT_STRUCT_H

#include "MyMsgQueue.h"
#include <memory>
#include <mutex>
#include <queue>
#include <string>

using pQueMsg = std::shared_ptr<MyMsgQueue>;

class ClientStruct
{
public:
    ClientStruct(int clitfd);
    void setRead(const int& originFlag, const int& targetFlag);
    const int& getClitFd();
    void Push(const std::string& msg);
    std::string Pop();

private:
    std::mutex mtRead;
    std::mutex mtWrite;
    //0无 1已上 2正做
    int readFlag;
    int writeFlag;
    int clitFd;
    pQueMsg qMsg;
};

#endif