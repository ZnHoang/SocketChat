#ifndef TASK_FUNCTION_H
#define TASK_FUNCTION_H

#include <memory>
#include <queue>
#include <string>
#include "MyMsgQueue.h"

using pQueMsg = std::shared_ptr<MyMsgQueue>;

class TaskFunction
{
public:
    TaskFunction() = delete;
    static void task1();
};

#endif