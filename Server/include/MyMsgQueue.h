#ifndef MY_QUEUE_H
#define MY_QUEUE_H

#include <queue>
#include <string>
#include <condition_variable>
#include <mutex>

class MyMsgQueue
{
public:
    void Push(const std::string& msg);
    std::string Pop();

private:
    bool isEmpty();

    std::queue<std::string> qMsg;
    std::mutex mt;
};

#endif