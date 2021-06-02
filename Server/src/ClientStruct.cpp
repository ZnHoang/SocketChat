#include "ClientStruct.h"

ClientStruct::ClientStruct(int clitfd)
    :   clitFd(clitfd),
        readFlag(false),
        writeFlag(false)
{

}

void ClientStruct::setRead(const int& originFlag, const int& targetFlag)
{
    
}

const int& ClientStruct::getClitFd()
{
    return clitFd;
}

void ClientStruct::Push(const std::string& msg)
{
    qMsg.get()->Push(msg);
}

std::string ClientStruct::Pop()
{
    return qMsg.get()->Pop();
}