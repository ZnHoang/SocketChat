#include "ClientStruct.h"

ClientStruct::ClientStruct(int clitfd)
    :   clitFd(clitfd),
        readFlag(ReadFlag::NONE),
        writeFlag(WriteFlag::NONE)
{

}

const ReadFlag ClientStruct::setRead(const std::unordered_map<ReadFlag, ReadFlag>& otFlags)
{
    std::unique_lock<std::mutex> lk(mtRead);
    auto it = otFlags.find(readFlag);
    auto originFlag = readFlag;
    if(it != otFlags.end())
    {
        readFlag = it->second;
    }
    return originFlag;
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