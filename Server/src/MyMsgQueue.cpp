#include "MyMsgQueue.h"
#include <iostream>

void MyMsgQueue::Push(const std::string& msg)
{
    ulm lk(mt);
    qMsg.push(msg);
}

std::string MyMsgQueue::Pop()
{
    ulm lk(mt);
    if(isEmpty())
    {
        return "";
    }
    std::string msg = qMsg.front();
    qMsg.pop();
    return msg;
}

bool MyMsgQueue::tryPop()
{
    ulm lk(mt);
    return !qMsg.empty();
}

bool MyMsgQueue::isEmpty()
{
    return qMsg.empty();
}