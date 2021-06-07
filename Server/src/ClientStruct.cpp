#include "ClientStruct.h"

ClientStruct::ClientStruct(int clitfd)
    :   clitFd(clitfd),
        readFlag(ReadFlag::NONE),
        writeFlag(WriteFlag::NONE),
        evs(EPOLLONESHOT)
{
    qMsg = std::make_shared<MyMsgQueue>();
}

const ReadFlag ClientStruct::setRead(const mRR& otFlags)
{
    ulm lk(mtRead);
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
    ulm lk(mtWrite);
    auto it = otFlags.find(writeFlag);
    auto originFlag = writeFlag;
    if(it != otFlags.end())
    {
        writeFlag = it->second;
    }
    return originFlag;
}

const int ClientStruct::addEvs(const int evs)
{
    this->evs |= evs;
    return this->evs;
}

const int ClientStruct::delEvs(const int evs)
{
    this->evs &= ~evs;
    return this->evs;
}

const int ClientStruct::getEvs()
{
    return evs;
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

bool ClientStruct::tryPop()
{
    return qMsg.get()->tryPop();
}