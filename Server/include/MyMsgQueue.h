#ifndef MY_MSG_QUEUE_H
#define MY_MSG_QUEUE_H

#include <queue>
#include <string>
#include <condition_variable>
#include <mutex>

using ulm = std::unique_lock<std::mutex>;

class MyMsgQueue
{
public:
    void Push(const std::string& msg);
    std::string Pop();
    bool tryPop();

private:
    bool isEmpty();

    std::queue<std::string> qMsg;
    std::mutex mt;
};

#endif