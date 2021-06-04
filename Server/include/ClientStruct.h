#ifndef CLIENT_STRUCT_H
#define CLIENT_STRUCT_H

#include "MyMsgQueue.h"
#include <memory>
#include <mutex>
#include <queue>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

enum class ReadFlag{NONE, READ, READING};
enum class WriteFlag{NONE, WRITE, WRITING};

using pQueMsg = std::shared_ptr<MyMsgQueue>;

class ClientStruct
{
public:
    ClientStruct(int clitfd);
    const ReadFlag setRead(const std::unordered_map<ReadFlag, ReadFlag>& otFlags);
    const int& getClitFd();
    void Push(const std::string& msg);
    std::string Pop();
private:
    std::mutex mtRead;
    std::mutex mtWrite;
    //0无 1已上 2正做
    ReadFlag readFlag;
    WriteFlag writeFlag;
    int clitFd;
    pQueMsg qMsg;
};

#endif