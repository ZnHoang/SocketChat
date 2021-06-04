#include "ClientStruct.h"

ClientStruct::ClientStruct(int clitfd)
    :   clitFd(clitfd),
        readFlag(ReadFlag::NONE),
        writeFlag(WriteFlag::NONE)
{

}

const ReadFlag ClientStruct::setRead(const mRR& otFlags)
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

const WriteFlag ClientStruct::setWrite(const mWW& otFlags)
{
    std::unique_lock<std::mutex> lk(mtWrite);
    auto it = otFlags.find(writeFlag);
    auto originFlag = writeFlag;
    if(it != otFlags.end())
    {
        writeFlag = it->second;
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