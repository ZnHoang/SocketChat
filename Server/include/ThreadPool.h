#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <iostream>
#include <queue>
#include <atomic>
#include <vector>
#include <thread>
#include <memory>
#include <functional>
#include <algorithm>
#include <chrono>
#include <mutex>
#include <condition_variable>

//优先度枚举类
enum class Priority
{
    LOW, MIDDLE, HIGH
};

const double priTime = 1.0; //每个优先度能够优先的时间（s）

using namespace std::chrono;
using task = std::function<void()>; //所要运行的函数

//任务结构体
using stTask = struct stTask
{
public:
    static time_point<steady_clock> startTime; //
    task t; //任务函数
    Priority priority; //任务优先度
    double diffTime = (steady_clock::now() - startTime).count(); //创建时间 

    //根据创建时间以及优先度进行优先队列的插入
    friend bool operator< (const stTask& a, const stTask& b)
    {
        auto A = a.diffTime - static_cast<int>(a.priority) * priTime;
        auto B = b.diffTime - static_cast<int>(b.priority) * priTime;
        return A < B;
    }
};

using pThr = std::shared_ptr<std::thread>;
using pSTk = std::shared_ptr<stTask>;

//线程池类
class ThreadPool
{
public:
    ThreadPool(uint size = 3);
    ~ThreadPool();
    ThreadPool(const ThreadPool& tp) = delete;
    const ThreadPool& operator= (const ThreadPool& tp) = delete;
    template <typename Func, typename... Args>
    void addTask(Priority prio, Func&& func, Args&&... args);

private:
    //初始化线程池内部件
    void init();
    //每个线程的执行函数（非外部传入的需要执行的函数）
    void run();
    //
    const task popTask();

    uint size; //线程池中所能开启的线程数量
    bool isStart; //线程池是否正在运行
    std::vector<pThr> vThreads; //存放所有线程
    std::priority_queue<pSTk> qTasks; //存放所有任务结构体的优先队列
    std::mutex mt; //qTasks存取锁
    std::condition_variable cv; //对lk能否解锁条件变量
    std::atomic<uint> countTasks;
};

template <typename Func, typename... Args>
void ThreadPool::addTask(Priority prio, Func&& func, Args&&... args)
{
    std::unique_lock<std::mutex> lk(mt);
    auto t = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
    task tas = [t](){t();};
    stTask st;
    st.priority = prio;
    st.t = tas;
    auto p{std::make_shared<stTask>(st)};
    qTasks.emplace(std::move(p));
    countTasks++;
    cv.notify_one();
}

#endif
