#include "MyMsgQueue.h"

void MyMsgQueue::Push(const std::string& msg)
{
    std::unique_lock<std::mutex> lk(mt);
    qMsg.push(msg);
}

std::string MyMsgQueue::Pop()
{
    std::unique_lock<std::mutex> lk(mt);
    if(isEmpty())
    {
        return "";
    }
    std::string msg = qMsg.front();
    qMsg.pop();
    return msg;
}

bool MyMsgQueue::isEmpty()
{
    return qMsg.empty();
}