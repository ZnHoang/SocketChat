#include "ThreadPool.h"

time_point<steady_clock> stTask::startTime = steady_clock::now();

ThreadPool::ThreadPool(uint size)
    :   size(size),
        isStart(false)
{
    init();
}

ThreadPool::~ThreadPool()
{
    isStart = false;
    cv.notify_all();
    for(auto i = 0; i < vThreads.size(); i++)
    {
        if(vThreads[i].get()->joinable())
        {
            vThreads[i].get()->join();
        }
    }
}

void ThreadPool::init()
{
    vThreads.reserve(size);
    for(auto i = 0; i < size; ++i)
    {
        auto pt{std::make_shared<std::thread>(&ThreadPool::run, this)};
        vThreads.emplace_back(std::move(pt));
    }
    while(!qTasks.empty())
    {   
        qTasks.pop();
    }
    countTasks = 0;
    isStart = true;
}

void ThreadPool::run()
{
    while(isStart)
    {
        auto t = popTask();
        if(isStart && t != NULL)
        {
            t();
        }
    }
}

const task ThreadPool::popTask()
{
    std::unique_lock<std::mutex> lk(mt);
    cv.wait(lk, [this](){return !this->isStart || this->countTasks > 0;});
    // if(isStart && countTasks == 0)
    // {
    //     cv.wait(lk);
    // }
    if(isStart && countTasks > 0)
    {
        auto t = qTasks.top().get()->t;
        qTasks.pop();
        countTasks--;   
        return t;
    }
    return NULL;
}